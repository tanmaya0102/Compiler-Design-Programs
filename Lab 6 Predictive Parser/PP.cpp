#include <bits/stdc++.h>
using namespace std;
int main()
{
    char fin[10][20], st[10][20], ft[20][20], fol[20][20];
    int a, i, t, b, n, j, s = 0, p;
    cout << "Enter the number of productions: ";
    cin >> n;
    cout << "Enter the productions of the grammar:\n";
    for (i = 0; i < n; i++)
        cin >> st[i];
    cout << "\nEnter the FIRST and FOLLOW of each non-terminal:";
    for (i = 0; i < n; i++)
    {
        cout << "\nFIRST[" << st[i][0] << "] : ";
        cin >> ft[i];
        cout << "FOLLOW[" << st[i][0] << "] : ";
        cin >> fol[i];
    }
    cout << "\nThe contents of the predictive parser table are:\n";
    for (i = 0; i < n; i++)
    {
        j = 3;
        while (st[i][j] != '\0')
        {
            if (st[i][j - 1] == '|' || j == 3)
            {
                for (p = 0; p <= 2; p++)
                    fin[s][p] = st[i][p];
                t = j;
                for (p = 3; st[i][j] != '|' && st[i][j] != '\0'; p++, j++)
                    fin[s][p] = st[i][j];
                fin[s][p] = '\0';
                if (st[i][t] == 'e')
                {
                    a = b = 0;
                    while (st[a++][0] != st[i][0])
                        ;
                    while (fol[a][b] != '\0')
                    {
                        cout << "M[" << st[i][0] << "," << fol[a][b]
                             << "] = " << fin[s] << "\n";
                        b++;
                    }
                }
                else if (!(st[i][t] > 64 && st[i][t] < 91))
                    cout << "M[" << st[i][0] << "," << st[i][t]
                         << "] = " << fin[s] << "\n";
                else
                {
                    a = b = 0;
                    while (st[a++][0] != st[i][3])
                        ;
                    while (ft[a][b] != '\0')
                    {
                        cout << "M[" << st[i][0] << "," << ft[a][b]
                             << "] = " << fin[s] << "\n";
                        b++;
                    }
                }
                s++;
            }
            if (st[i][j] == '|')
                j++;
        }
    }
    return 0;
}
