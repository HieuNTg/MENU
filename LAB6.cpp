#include<iostream>
#include<string>
#include<iomanip>
using namespace std;


struct pageNumber
{
    int sequencePage[100];
    int idx[100];
    string PageFault;
};

int MINidx(pageNumber *pN, int i, int m)
{
    int min= 0;
    for (int j=0; j<m; j++)
    {
        if (pN[i].idx[j] < pN[i].idx[min])
            min = j;
    }
    return min;
}

int FINDidx(pageNumber *pN, int i, int m, int n, int a[])
{
    int max = 0;
    int idx = 0;
    for (int j=0; j<m; j++)
    {
        bool check = false;
        for (int temp=i+1;temp < n;temp++)
        {
            if (a[temp] == pN[i].sequencePage[j])
                check = true;
        }
        if (check == false)
            return j;
        for (int temp=i+1;temp < n;temp++)
        {
            if (a[temp] == pN[i].sequencePage[j] && temp > max)
            {
                max = temp;
                idx = j;
                break;
            }
        }
    }
    return idx;
}

void FIFO(pageNumber *pN, int n, int m, int sequence[])
{
    for (int i = 0; i<n; i++)
        for (int j=0; j < m; j++)
        {
            pN[i].sequencePage[j] = -1;
            pN[i].idx[j] = -1;
        }
    for (int i = 0; i<n; i++)
    {
        int avaible = 0;
        for (int j=0; j < m; j++)
            if (sequence[i] == pN[i].sequencePage[j])
                avaible = 1;
        if (avaible == 0)
        {
            int a = MINidx(pN,i,m);
            for (int j=0; j < m; j++)
            {
                if (pN[i].sequencePage[j] == -1)
                {
                    pN[i].sequencePage[j] = sequence[i];
                    pN[i].PageFault = "*";
                    break;
                }
            }
            for (int j=0; j < m; j++)
            {
                if (j == a)
                {
                    pN[i].sequencePage[j] = sequence[i];
                    pN[i].idx[j] = i;
                    pN[i].PageFault = "*";
                    break;
                }
            }
        }
        for (int j = 0;j<m;j++)
        {
            pN[i+1].sequencePage[j]=pN[i].sequencePage[j];
            pN[i+1].idx[j]=pN[i].idx[j];
        }
    }
    cout <<" _____________________________________\n";
    cout <<"|---FIFO Page Replacement Algorithm---|\n";
    cout <<"|_____________________________________|\n";
    
    for (int i=0;i<n;i++)
        cout<<setw(4)<<sequence[i]<<setw(4);
    cout<<endl;
    for (int j=0;j<m;j++)
    {
        for (int i =0;i<n;i++)
        {
            if (pN[i].sequencePage[j] != -1)
                cout<<pN[i].sequencePage[j]<<setw(4);
            else
                cout<<" "<<setw(4);
        }
        cout<<endl;
    }
    int dem=0;
    for (int i=0;i<n;i++)
    {
        if (pN[i].PageFault == "*")
            dem++;
        cout<<pN[i].PageFault<<setw(4);
    }
    cout << endl;
    cout << "Number of Page Fault: " << dem;
}

void OPT(pageNumber *pN, int n, int m, int sequence[])
{
    for (int i = 0; i<n; i++)
        for (int j=0; j < m; j++)
        {
            pN[i].sequencePage[j] = -1;
        }
    for (int i = 0; i<n; i++)
    {
        int avaible = 0;
        for (int j=0; j < m; j++)
            if (sequence[i] == pN[i].sequencePage[j])
                avaible = 1;
        if (avaible == 0)
        {
            int idx = FINDidx(pN,i,m,n,sequence);
            for (int j=0; j < m; j++)
            {
                if (pN[i].sequencePage[j] == -1)
                {
                    pN[i].sequencePage[j] = sequence[i];
                    pN[i].PageFault = "*";
                    break;
                }
            }
           
            bool check = true ;
            for (int j=0; j < m; j++)
            {
                if (pN[i].sequencePage[j] == -1 || pN[i].sequencePage[j]==sequence[i])
                    check = false;
            }
            if (check == true)
            {
                pN[i].sequencePage[idx] = sequence[i];
                pN[i].PageFault = "*";
            }
                
        }
        for (int j = 0;j<m;j++)
        {
            pN[i+1].sequencePage[j]=pN[i].sequencePage[j];
        }
    }
    cout <<" ____________________________________\n";
    cout <<"|---OPT Page Replacement Algorithm---|\n";
    cout <<"|____________________________________|\n";
    
    for (int i=0;i<n;i++)
        cout<<setw(4)<<sequence[i]<<setw(4);
    cout<<endl;
    for (int j=0;j<m;j++)
    {
        for (int i =0;i<n;i++)
        {
            if (pN[i].sequencePage[j] != -1)
                cout<<pN[i].sequencePage[j]<<setw(4);
            else
                cout<<" "<<setw(4);
        }
        cout<<endl;
    }
    int dem=0;
    for (int i=0;i<n;i++)
    {
        if (pN[i].PageFault == "*")
            dem++;
        cout<<pN[i].PageFault<<setw(4);
    }
    cout << endl;
    cout << "Number of Page Fault: " << dem;
}

void LRU(pageNumber *pN, int n, int m, int sequence[])
{
    for (int i = 0; i<n; i++)
        for (int j=0; j < m; j++)
        {
            pN[i].sequencePage[j] = -1;
            pN[i].idx[j] = -1;
        }
    for (int i = 0; i<n; i++)
    {
        int avaible = 0;
        for (int j=0; j < m; j++)
            if (sequence[i] == pN[i].sequencePage[j])
                avaible = 1;
        if (avaible == 0)
        {
            int a = MINidx(pN,i,m);
            for (int j=0; j < m; j++)
            {
                if (pN[i].sequencePage[j] == -1)
                {
                    pN[i].sequencePage[j] = sequence[i];
                    pN[i].PageFault = "*";
                    break;
                }
            }
            for (int j=0; j < m; j++)
            {
                if (j == a)
                {
                    pN[i].sequencePage[j] = sequence[i];
                    pN[i].idx[j] = i;
                    pN[i].PageFault = "*";
                    break;
                }
            }
        }
        else 
        {
            for (int j=0; j < m; j++)
                if (pN[i].sequencePage[j]==sequence[i])
                    pN[i].idx[j]=i;
        }
        for (int j = 0;j<m;j++)
        {
            pN[i+1].sequencePage[j]=pN[i].sequencePage[j];
            pN[i+1].idx[j]=pN[i].idx[j];
        }
    }
    cout <<" ____________________________________\n";
    cout <<"|---LRU Page Replacement Algorithm---|\n";
    cout <<"|____________________________________|\n";
    
    
    for (int i=0;i<n;i++)
        cout<<setw(4)<<sequence[i]<<setw(4);
    cout<<endl;
    for (int j=0;j<m;j++)
    {
        for (int i =0;i<n;i++)
        {
            if (pN[i].sequencePage[j] != -1)
                cout<<pN[i].sequencePage[j]<<setw(4);
            else
                cout<<" "<<setw(4);
        }
        cout<<endl;
    }
    int dem=0;
    for (int i=0;i<n;i++)
    {
        if (pN[i].PageFault == "*")
            dem++;
        cout<<pN[i].PageFault<<setw(4);
    }
    cout << endl;
    cout << "Number of Page Fault: " << dem;
}

int main()
{
    cout<<" _________________________________________\n";
    cout<<"|  -----Page Replacement Algorithm-----   |\n";
    cout<<"|      1. Default referenced sequence     |\n";
    cout<<"|      2. Manual input sequence           |\n";
    cout<<"|_________________________________________|\n";
    int choice;
    pageNumber *pN;
    int sequence[100];
    int n,m;
    do
    {
        cout<< "Your choice: ";
        cin>> choice;
    }while(choice != 1 && choice != 2);
    if(choice == 2)
    {
        cout<<"Input number of Sequence Page: ";
        cin >> n;
        cout <<"Referenced sequence: ";
        for (int i=0; i<n; i++)
            cin >> sequence[i];
    }
    else
    {
        int sequence1[] = {2, 0, 5, 2, 0, 1, 8, 4, 0, 0, 7};
        n = 11;
        for(int i = 0; i < n; i++)
            sequence[i] = sequence1[i];
    }
    
    
    cout <<"|  -----Page Replacement Algorithm-----   |\n";
    cout <<"           Input page frames: ";
    cin >> m;
    
    cout <<" ________________________________________\n";
    cout <<"|  -----Page Replacement Algorithm-----  |\n";
    cout <<"|          1. FIFO algorithm             |\n";
    cout <<"|          2. OPT algorithm              |\n";
    cout <<"|          3. LRU algorithm              |\n";
    cout <<"|________________________________________|\n";
    
    int choice2;
    do
    {
        cout <<"Your choice (1->3): ";
        cin>>choice2;
    }while(choice2 < 1 && choice2 > 3);
    
    pN = new pageNumber[n];
    switch (choice2)
    {
        case 1: 
            FIFO(pN, n, m, sequence);
            break;
        case 2: 
            OPT(pN, n, m, sequence);
            break;
        case 3:
            LRU(pN, n, m, sequence);
            break;
    }
    return 1;
}


