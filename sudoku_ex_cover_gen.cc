#include<iostream>
#include<cstdio>
using namespace std;
int main(){
    int a[9][9];
    FILE *fp1,*fp2;
    cout<<"Enter the given 9 * 9 matrix for sudoku,Enter 0 for empty cells\n";
    int i,j,w;
    fp1=fopen("row_format.txt","w");
    w=0;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            scanf("%d",&a[i][j]);
            if(a[i][j]!=0){
                fprintf(fp1,"%d ",a[i][j]);
                fprintf(fp1,"%d ",i);
                fprintf(fp1,"%d ",j);
                if((i>=0)&&(i<=2)){
                    if((j>=0)&&(j<=2))
                        fprintf(fp1,"0\n");
                    else if((j>=3)&&(j<=5))
                        fprintf(fp1,"1\n");
                    else if((j>=6)&&(j<=8))
                        fprintf(fp1,"2\n");
                }
                else if((i>=3)&&(i<=5)){
                    if((j>=0)&&(j<=2))
                        fprintf(fp1,"3\n");
                    else if((j>=3)&&(j<=5))
                        fprintf(fp1,"4\n");
                    else if((j>=6)&&(j<=8))
                        fprintf(fp1,"5\n");
                }
                else if((i>=6)&&(i<=8)){
                    if((j>=0)&&(j<=2))
                        fprintf(fp1,"6\n");
                    else if((j>=3)&&(j<=5))
                        fprintf(fp1,"7\n");
                    else if((j>=6)&&(j<=8))
                        fprintf(fp1,"8\n");
                }
                w++;
            }
            else if(a[i][j]==0){
                int u;
                for(u=1;u<=9;u++){
                    fprintf(fp1,"%d ",u);
                    fprintf(fp1,"%d ",i);
                    fprintf(fp1,"%d ",j);
                    if((i>=0)&&(i<=2)){
                        if((j>=0)&&(j<=2))
                            fprintf(fp1,"0\n");
                        else if((j>=3)&&(j<=5))
                            fprintf(fp1,"1\n");
                        else if((j>=6)&&(j<=8))
                            fprintf(fp1,"2\n");
                    }
                    else if((i>=3)&&(i<=5)){
                        if((j>=0)&&(j<=2))
                            fprintf(fp1,"3\n");
                        else if((j>=3)&&(j<=5))
                            fprintf(fp1,"4\n");
                        else if((j>=6)&&(j<=8))
                            fprintf(fp1,"5\n");
                    }
                    else if((i>=6)&&(i<=8)){
                        if((j>=0)&&(j<=2))
                            fprintf(fp1,"6\n");
                        else if((j>=3)&&(j<=5))
                            fprintf(fp1,"7\n");
                        else if((j>=6)&&(j<=8))
                            fprintf(fp1,"8\n");
                    }
                    w++;
                }
            }
        }
    }
    fclose(fp1);
    int v,z,x[4],x1[324],v1,v2[2];
    fp1=fopen("row_format.txt","r");
    fp2=fopen("ex_cover.txt","w");
    v1=0;
    v2[0]=0;
    v2[1]=0;
    fprintf(fp2,"%d\n",w);
    for(z=0;z<w;z++){
        fscanf(fp1,"%d%d%d%d",&x[0],&x[1],&x[2],&x[3]);
        for(v=0;v<324;v++){
            x1[v]=0;
        }
        if((v2[0]==x[1])&&(v2[1]==x[2])){
            v2[0]=x[1];
            v2[1]=x[2];
        }
        else{
            v2[0]=x[1];
            v2[1]=x[2];
            v1++;
        }
        x1[v1]=1;
        x1[80+9*x[1]+x[0]]=1;
        x1[161+9*x[2]+x[0]]=1;
        x1[242+9*x[3]+x[0]]=1;
        for(v=0;v<323;v++){
            fprintf(fp2,"%d ",x1[v]);
        }
        fprintf(fp2,"%d\n",x1[v]);
    }
    fclose(fp1);
    fclose(fp2);
    return(0);
}
