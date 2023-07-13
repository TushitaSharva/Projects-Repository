#include <iostream>
#include <vector>
#include <string>
using namespace std;

int power(int x, int y)
{
    int result = 1;
    for (int i = 0; i < y; ++i)
        result *= x;
    return result;
}

void printmap(vector<vector<int>> &map);
string convDecToBin(int x);
bool check_diff_by1(string first, string second);
string Dash(string first, string second);
string BinaryToLiteral(string x);
vector<string> simplify(vector<string> &binaryMinterms, vector<int> &minterms);
bool inVec(vector<string> vec, string x);
void secVariable(vector<int> &minterms, vector<vector<int>> &map);
void threeVariable(vector<int> &minterms, vector<vector<int>> &map);
void oneVaribale(vector<int> &minterms, vector<vector<int>> &map);

int main()
{
    vector<int> minterms;
    int numOfMinterms;
    int kmapVariable;
    cout << "\nA, B, and C are available literals."
         << "\n";
    cout << "\nEnter no of variables among {1, 2, 3}: ";
    cin >> kmapVariable;
    if (kmapVariable != 1 && kmapVariable != 2 && kmapVariable != 3)
    {
        cout << "Wrong input variable! Please select among {1,2,3}\n";
        return 0;
    }
    cout << "\nEnter number of minterms (must be <= or = " << power(2, kmapVariable) << " and positive): ";
    while (true)
    {
        cin >> numOfMinterms;
        if (cin.fail() || numOfMinterms <= 0 || numOfMinterms > power(2, kmapVariable))
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Wrong input!! Must be integer and >=0 and <= " << power(2, kmapVariable) << "\n";
        }
        else
            break;
    }
    int y = power(2, kmapVariable);
    cout << "\nEnter the minterms: ";
    cout << "(must be integers >= 0 and <= " << y << ")"
         << "\n";
    int x;
    while (numOfMinterms > 0)
    {
        cin >> x;
        if (cin.fail() || x < 0 || x > y - 1)
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Wrong input!! Must be integer and >= 0 and <= " << y << "\n";
        }
        else
        {
            minterms.push_back(x);
            numOfMinterms--;
        }
    }
    cout << "\nThe minterms are: "
         << "\n";
    for (int i = 0; i < minterms.size(); i++)
        cout << minterms.at(i) << " ";
    cout << "\n"
         << "\n";
    vector<vector<int>> map;
    switch (kmapVariable)
    {
    case 1:
        oneVaribale(minterms, map);
        break;
    case 2:
        secVariable(minterms, map);
        break;
    case 3:
        threeVariable(minterms, map);
        break;
    default:
        cout << "Wrong input! You should select among 1,2,3.\n";
        break;
        cout << "\n";
        return 0;
    }
}
vector<string> simplify(vector<string> &binaryMinterms, vector<int> &minterms)
{
    vector<string> updatedMinterms;
    int size = binaryMinterms.size();
    vector<int> taken;
    taken.resize(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (check_diff_by1(binaryMinterms[i], binaryMinterms[j]))
            {
                taken[i] = 1;
                taken[j] = 1;
                string temp = Dash(binaryMinterms[i], binaryMinterms[j]);
                if (!inVec(updatedMinterms, temp))
                    updatedMinterms.push_back(temp);
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (taken[i] != 1 && !inVec(updatedMinterms, binaryMinterms[i]))
            updatedMinterms.push_back(binaryMinterms[i]);
    }
    return updatedMinterms;
}
bool inVec(vector<string> vec, string x)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (x == vec[i])
            return true;
    }
    return false;
}
string BinaryToLiteral(string x)
{
    vector<string> literals = {"A", "B", "C"};
    string result = "";
    for (int i = 0; i < x.length(); i++)
    {
        if (x[i] != '-')
        {
            if (x[i] == '1')
                result += literals[i];
            else if (x[i] == '0')
                result += literals[i] + "'";
        }
    }
    return result;
}
string Dash(string first, string second)
{
    string result = "";
    for (int i = 0; i < 3; i++)
    {
        if (first[i] != second[i])
            result = result + "-";
        else
            result += first[i];
    }
    return result;
}
bool check_diff_by1(string first, string second)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        if (first[i] != second[i])
            count++;
    }
    if (count == 1)
        return true;
    else
        return false;
}
string convDecToBin(int x)
{
    string binary = "";
    while (x)
    {
        if (x & 1)
            binary = "1" + binary;
        else
            binary = "0" + binary;
        x >>= 1;
    }
    while (binary.length() != 3)
        binary = "0" + binary;
    return binary;
}
void printmap(vector<vector<int>> &map)
{
    cout << "K-MAP: "
         << "\n";
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}
void secVariable(vector<int> &minterms, vector<vector<int>> &map)
{
    map.resize(2);
    for (int i = 0; i < map.size(); i++)
        map[i].resize(2);
    int j;
    for (int i = 0; i < minterms.size(); i++)
    {
        int a = minterms.at(i);
        if (a < 2)
            j = 0;
        else
        {
            j = 1;
            a = a - 2;
        }
        map[a][j] = 1;
    }
    printmap(map);
    if (minterms.size() == 4)
    {
        cout << "The final simplified expression = 1 " << "\n ";
    }
    else if (minterms.size() == 1)
    {
        int n = 0, m = 0;
        bool y = true;
        for (int i = 0; i < map.size(); i++)
        {
            for (int j = 0; j < map[i].size(); j++)
            {
                if (map[i][j] == 1)
                {
                    y = false;
                    break;
                }
                else
                {
                    if (n == 1)
                        m++;
                    n++;
                }
            }
            if (y == false)
            {
                break;
            }
        }
        if (m == 0)
        {
            if (n == 0)
            {
                cout << "The final simplified expression = A'B'" << "\n";
            }
            else if (n == 1)
            {
                cout << "The final simplified expression = AB'" << "\n";
            }
        }
        else if (m == 1)
        {
            if (n == 2)
            {
                cout << "The final simplified expression = A'B" << "\n";
            }
            else if (n == 3)
            {
                cout << "The final simplified expression = AB " << "\n ";
            }
        }
    }
    else if (minterms.size() == 3)
    {
        int n = 0;
        int m = 0;
        bool y = true;
        for (int i = 0; i < map.size(); i++)
        {
            for (int j = 0; j < map[i].size(); j++)
            {
                if (map[i][j] == 0)
                {
                    y = false;
                    break;
                }
                else
                {
                    if (n == 1)
                        m++;
                    n++;
                }
            }
            if (y == false)
            {
                break;
            }
        }
        if (m == 0)
        {
            if (n == 0)
            {
                cout << "F = A + B" << "\n";
            }
            else if (n == 1)
            {
                cout << "F = A' + B" << "\n";
            }
        }
        else if (m == 1)
        {
            if (n == 2)
            {
                cout << "F = A + B'" << "\n";
            }
            else if (n == 3)
            {
                cout << "F = A' + B'" << "\n";
            }
        }
    }
    else if (minterms.size() == 2)
    {
        int k = 0;
        int f = 0;
        int z = 0;
        bool x = false;
        bool y = true;
        for (int i = 0; i < map.size(); i++)
        {
            for (int j = 0; j < map[i].size(); j++)
            {
                if (map[i][j] == 0)
                    k++;
                else if (map[i][j] == 1 && !x)
                {
                    k++;
                    f = k;
                    x = true;
                }
                else if (map[i][j] == 1 && x)
                {
                    k++;
                    z = k;
                    y = false;
                    break;
                }
            }
            if (y == false)
            {
                break;
            }
        }
        f--;
        z--;
        if (f == 0 && z == 1)
        {
            cout << "The final simplified expression = B'" << "\n";
        }
        else if (f == 2 && z == 3)
        {
            cout << "The final simplified expression = B " << "\n ";
        }
        else if (f == 0 && z == 2)
        {
            cout << "The final simplified expression = A'" << "\n";
        }
        else if (f == 1 && z == 3)
        {
            cout << "The final simplified expression = A " << "\n ";
        }
        else if (f == 0 && z == 3)
        {
            cout << "The final simplified expression = A 'B' + AB " << "\n ";
        }
        else if (f == 1 && z == 2)
        {
            cout << " The final simplified expression = AB ' + A' B " << "\n ";
        }
    }
}

void threeVariable(vector<int> &minterms, vector<vector<int>> &map)
{
    map.resize(2);
    for (int i = 0; i < map.size(); i++)
        map[i].resize(4);
    for (int i = 0; i < minterms.size(); i++)
    {
        int m = 0;
        int n = 0;
        int x = 0;
        for (int j = 0; j <= minterms[i]; j++)
        {
            if (x == minterms[i])
            {
                map[m][n] = 1;
                break;
            }
            else
            {
                if (m == 0)
                    m++;
                else if (m == 1)
                {
                    m = 0;
                    n++;
                }
                x++;
            }
        }
    }
    swap(map[0][2], map[0][3]);
    swap(map[1][2], map[1][3]);
    printmap(map);
    if (minterms.size() == 8)
    {
        cout << "F = 1"
             << "\n";
    }
    else
    {
        vector<string> binaryMinterms;
        for (int i = 0; i < minterms.size(); i++)
            binaryMinterms.push_back(convDecToBin(minterms.at(i)));
        do
        {
            binaryMinterms = simplify(binaryMinterms, minterms);
        } while (!(binaryMinterms == simplify(binaryMinterms, minterms)));

        cout << "F = ";

        for (int i = 0; i < binaryMinterms.size(); i++)
        {
            if (i != binaryMinterms.size() - 1)
            {
                cout << BinaryToLiteral(binaryMinterms[i]) << " + ";
            }
            else
            {
                cout << BinaryToLiteral(binaryMinterms[i]) << "\n";
            }
        }
    }
}
void oneVaribale(vector<int> &minterms, vector<vector<int>> &map)
{
    map.resize(1);
    map[0].resize(2);

    for (int i = 0; i < minterms.size(); i++)
    {
        int a = minterms.at(i);
        map[0][a] = 1;
    }

    printmap(map);

    if (minterms.size() == 2)
    {
        cout << "The final simplified expression = 1 " << "\n ";
    }
    else if (minterms.size() == 1)
    {
        if (map[0][0] == 1)
        {
            cout << "The final simplified expression = A'" << "\n";
        }
        else if (map[0][1] == 1)
        {
            cout << "The final simplified expression = A " << "\n ";
        }
    }
}
