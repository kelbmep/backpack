#include <bits/stdc++.h>

using namespace std;

int firstNonZeroBit(int a)
{
    int i = 0;
    while(a != 0)
    {
        if(a % 2 == 1)
            return i;
        a /= 2;
        i++;
    }
    return 0;
}
struct thing{
    long long value;
    long long weight;
    bitset<32> sequence;
};

bool compare(thing a, thing b)
{
    if(a.value == b.value)
        return a.weight > b.weight;
    else
        return a.value > b.value;
}

int main()
{
    int n, W;
    fstream fin("input.txt");
    fin >> n >> W;
    int* w = new int[n];
    int* p = new int[n];
    for (int i = 0; i < n; i++)
        fin >> w[i] >> p[i];
    if(n == 1 && w[0] <= W)
    {
        cout << 1 << endl << 1 << endl;
        return 0;
    }
    const unsigned int nIterations = 1 << (n / 2);
    long long sumW = 0;
    long long sumP = 0;
    bitset<32> mask;
    thing* firstGroup = new thing[nIterations];
    for (unsigned int i = 0; i < nIterations; i++)
    {
        unsigned long position;
        position = firstNonZeroBit(i);
        mask.flip(position);
        if (mask[position])
        {
            sumW += w[position];
            sumP += p[position];
            firstGroup[i].sequence = mask;
            firstGroup[i].weight = sumW;
            if (sumW > W)
                firstGroup[i].value = 0;
            else
                firstGroup[i].value = sumP;
        }
        else
        {
            sumW -= w[position];
            sumP -= p[position];
            firstGroup[i].sequence = mask;
            firstGroup[i].weight = sumW;
            if (sumW > W)
                firstGroup[i].value = 0;
            else
                firstGroup[i].value = sumP;
        }
    }
    sort(firstGroup, firstGroup + nIterations, compare);
    const unsigned int nIterations1 = 1 << (n / 2 + n % 2);
    sumW = 0;
    sumP = 0;
    mask = 0;
    thing* secondGroup = new thing[nIterations1];
    for(unsigned int i = 0; i < nIterations1; i++)
    {
        unsigned long position;
        position = firstNonZeroBit(i);
        mask.flip(position);
        if (mask[position])
        {
            sumW += w[position + n / 2];
            sumP += p[position + n / 2];
            secondGroup[i].sequence = mask;
            secondGroup[i].weight = sumW;
            if (sumW > W)
                secondGroup[i].value = 0;
            else
                secondGroup[i].value = sumP;
        }
        else
        {
            sumW -= w[position + n / 2];
            sumP -= p[position + n / 2];
            secondGroup[i].sequence = mask;
            secondGroup[i].weight = sumW;
            if (sumW > W)
                secondGroup[i].value = 0;
            else
                secondGroup[i].value = sumP;
        }
    }
    long long bestP = 0;
    bitset<32> bestMask1 = 0;
    bitset<32> bestMask2 = 0;
    for(unsigned int  i = 0; i < nIterations1; i++)
    {
        int mid = 0;
        int left = 0;
        int right = nIterations - 1;
        while(left < right)
        {
            mid = (right + left) / 2;
            if(firstGroup[mid].value + secondGroup[i].value < bestP)
                left = mid + 1;
            else
                right = mid - 1;
        }
        if(mid >= 1)
            mid--;
        for(unsigned int j = mid; j < nIterations; j++)
        {
            if(firstGroup[j].weight + secondGroup[i].weight > W)
                continue;
            else if(firstGroup[j].value + secondGroup[i].value > bestP)
            {
                bestP = firstGroup[j].value + secondGroup[i].value;
                bestMask1 = firstGroup[j].sequence;
                bestMask2 = secondGroup[i].sequence;
            }
        }
    }
    cout << bestMask1.count() + bestMask2.count() << endl;
    for (int i = 0; i < n / 2; i++)
        if (bestMask1[i] == 1)
            cout << i + 1 << " ";
    for (int i = 0; i < n / 2 + n % 2; i++)
        if (bestMask2[i] == 1)
            cout << i + n / 2 + 1 << " ";
    cout << endl;
    return 0;
}
