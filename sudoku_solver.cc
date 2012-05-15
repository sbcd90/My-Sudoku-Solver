#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#define n1 2000
#define n2 236197
using namespace std;
struct node{
    int name;
    int size;
    int rownum;
    int colnum;
    int startpos;
    struct node *left;
    struct node *right;
    struct node *up;
    struct node *down;
};
struct node *tempds[n2];
int n,u,a[n1/2][n1/2];
vector <int> x(n1);
vector <vector <int> > x1;
void createds(void);
void search(int);
struct node * choose_col(void);
void cover(struct node *);
void uncover(struct node *);
int main(){
    FILE *fp1,*fp2;
    int i,j;
    fp1=fopen("ex_cover.txt","r");
    fp2=fopen("row_format.txt","r");
    //cout<<"Enter the number of rows in the exact cover matrix\n";
    fscanf(fp1,"%d",&n);
    u=324;
    //cout<<"Enter the binary exact cover matrix\n";
    for(i=0;i<n;i++){
        for(j=0;j<u;j++){
            fscanf(fp1,"%d",&a[i][j]);
        }
    }
    int z[4];
    for(i=0;i<n;i++){
        fscanf(fp2,"%d%d%d%d",&z[0],&z[1],&z[2],&z[3]);
        x1.resize(x1.size()+1);
        x1[x1.size()-1].resize(3);
        x1[x1.size()-1][0]=z[1];
        x1[x1.size()-1][1]=z[2];
        x1[x1.size()-1][2]=z[0];
    }
    createds();
    search(0);
    fclose(fp1);
    fclose(fp2);
    //cout<<tempds[1]->up->rownum<<" "<<tempds[1]->down->right->colnum<<" "<<tempds[1]->right->up->rownum<<"\n";
    return(0);
}
void createds(void){
    int i,j,w,f,z,s,s1,s2;
    tempds[0]=(struct node *)malloc(sizeof(struct node));
    tempds[0]->name=0;
    tempds[0]->size=0;
    tempds[0]->startpos=-1;
    for(j=0;j<u;j++){
        tempds[j+1]=(struct node *)malloc(sizeof(struct node));
        tempds[j+1]->name=j+1;
        tempds[j+1]->left=tempds[j];
        tempds[j]->right=tempds[j+1];
    }
    tempds[0]->left=tempds[j];
    tempds[j]->right=tempds[0];
    w=(j+1);
    for(j=0;j<u;j++){
        f=0;
        tempds[j+1]->startpos=w;
        for(i=0;i<n;i++){
            if(a[i][j]==1){
                tempds[w]=(struct node *)malloc(sizeof(struct node));
                tempds[w]->rownum=i;
                tempds[w]->colnum=j+1;
                if(f==0){
                    tempds[w]->up=tempds[j+1];
                    tempds[j+1]->down=tempds[w];
                    f=1;
                }
                else{
                    tempds[w]->up=tempds[w-1];
                    tempds[w-1]->down=tempds[w];
                    f++;
                }
                w++;
            }
        }
        tempds[j+1]->up=tempds[w-1];
        tempds[w-1]->down=tempds[j+1];
        tempds[j+1]->size=f;
    }
    for(i=0;i<n;i++){
        f=0;
        for(j=0;j<u;j++){
            if(a[i][j]==1){
                s=0;
                for(z=0;z<i;z++){
                    if(a[z][j]==1)
                        s++;
                }
                s=tempds[j+1]->startpos+s;
                if(f>0){
                    tempds[s]->left=tempds[s1];
                    tempds[s1]->right=tempds[s];
                }
                else if(f==0){
                    f=1;
                    s2=s;
                }
                s1=s;
            }
        }
        tempds[s2]->left=tempds[s1];
        tempds[s1]->right=tempds[s2];
    }
}
void search(int k){
    int i,j;
    if(tempds[0]->right==tempds[0]){
        int x2[9][9];
        for(i=0;(x[i]!=0)&&(i<n1);i++){
            //cout<<x[i]<<"\n";
            x2[x1[x[i]-1][0]][x1[x[i]-1][1]]=x1[x[i]-1][2];
        }
        cout<<"The generated sudoku solution is:\n";
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                cout<<x2[i][j]<<" ";
            }
            cout<<"\n";
        }
        exit(0);
        return;
    }
    struct node *temp1=(struct node *)malloc(sizeof(struct node));
    temp1=choose_col();
    cover(temp1);
    struct node *temp2=(struct node *)malloc(sizeof(struct node));
    temp2=temp1->down;
    for(;temp2!=temp1;temp2=temp2->down){
        x[k]=temp2->rownum+1;
        struct node *temp3=(struct node *)malloc(sizeof(struct node));
        temp3=temp2->right;
        for(;temp3!=temp2;temp3=temp3->right){
            cover(tempds[temp3->colnum]);
        }
        search(k+1);
        temp3=temp2->left;
        for(;temp3!=temp2;temp3=temp3->left){
            uncover(tempds[temp3->colnum]);
        }
    }
    uncover(temp1);
}
struct node * choose_col(void){
    struct node *temp4=(struct node *)malloc(sizeof(struct node));
    temp4=tempds[0]->right;
    if(temp4!=tempds[0])
        return(temp4);
    else
        return(NULL);
}
void cover(struct node *c){
    c->right->left=c->left;
    c->left->right=c->right;
    int updates;
    struct node *temp5=(struct node *)malloc(sizeof(struct node));
    temp5=c->down;
    for(;temp5!=c;temp5=temp5->down){
        struct node *temp6=(struct node *)malloc(sizeof(struct node));
        temp6=temp5->right;
        for(;temp6!=temp5;temp6=temp6->right){
            temp6->down->up=temp6->up;
            temp6->up->down=temp6->down;
            tempds[temp6->colnum]->size=tempds[temp6->colnum]->size-1;
            updates++;
        }
    }
}
void uncover(struct node *c1){
    struct node *temp7=(struct node *)malloc(sizeof(struct node));
    temp7=c1->up;
    for(;temp7!=c1;temp7=temp7->up){
        struct node *temp8=(struct node *)malloc(sizeof(struct node));
        temp8=temp7->left;
        for(;temp8!=temp7;temp8=temp8->left){
            tempds[temp8->colnum]->size=tempds[temp8->colnum]->size+1;
            temp8->down->up=temp8;
            temp8->up->down=temp8;
        }
    }
    c1->right->left=c1;
    c1->left->right=c1;
}
