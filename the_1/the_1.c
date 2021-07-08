#include <stdio.h>
#define LEN 25

int pic[LEN][LEN];
int matrix[LEN/2][LEN/2];
int call=1,change=0;
int choose_color(int x,int y);
int fill_pic(int x,int y,int color,int i_color);
int copy_paste(int cr1,int cc1,int cr2,int cc2,int pr1,int pc1,int pr2,int pc2);
int copy_array(int sr,int sc,int br,int bc,int D);
int rotating(int sr,int sc,int len,int mat[][LEN/2],int D);
int x,y,i,j;

int main(){
    int pixel, xc, yc, xi, yi, c_color,init_color;
    int f_cr1,f_cc1,f_cr2,f_cc2,f_pr1,f_pc1,f_pr2,f_pc2;
    int degree,sr,sc,br,bc ; 
    char direction;
    char opcode;
    for( x=0;x<LEN;x++){
        for( y=0;y<LEN;y++){
            scanf("%d ", &pixel);
            pic[x][y]=pixel;
        }
    }
    scanf(" %c", &opcode);
    switch(opcode){
        case 'F': 
            scanf("%d %d",&xc,&yc);
            c_color=choose_color(xc,yc);
            scanf("%d %d",&xi,&yi);
            init_color=pic[xi][yi];
            fill_pic(xi, yi, c_color, init_color);
            for( i=0;i<LEN;i++){
                for( j=0;j<LEN;j++){
                    if(call==LEN){
                        call=1;
                        printf("%d\n", pic[i][j]);
                    }    
                    else{
                        call++;
                        printf("%d ", pic[i][j]); 
                    } 
                }
            }
            break;

        case 'P':
            scanf("%d %d %d %d",&f_cr1,&f_cc1,&f_cr2,&f_cc2);
            scanf("%d %d %d %d",&f_pr1,&f_pc1,&f_pr2,&f_pc2);
            copy_paste(f_cr1,f_cc1,f_cr2,f_cc2,f_pr1,f_pc1,f_pr2,f_pc2);
            for( i=0;i<LEN;i++){
                for( j=0;j<LEN;j++){
                    if(call==LEN){
                        call=1;
                        printf("%d\n", pic[i][j]);
                    }    
                    else{
                        call++;
                        printf("%d ", pic[i][j]); 
                    } 
                }
            }
            printf("%d\n",change);
            break;

        case 'R':
            scanf(" %c %d",&direction,&degree);
            scanf("%d %d %d %d",&sr,&sc,&br,&bc);
            if(direction=='L') copy_array(sr,sc,br,bc,degree);
            else if(direction=='R') copy_array(sr,sc,br,bc,(360-degree));
            else;
            for( i=0;i<LEN;i++){
                for( j=0;j<LEN;j++){
                    if(call==LEN){
                        call=1;
                        printf("%d\n", pic[i][j]);
                    }    
                    else{
                        call++;
                        printf("%d ", pic[i][j]); 
                    } 
                }
            }
            printf("%d\n",change);
            break;

    }
    return 0;
}

int choose_color(int x,int y){
    int color;
    if((0<=x) && (x<LEN) && (0<=y) && (y<LEN)) color=pic[x][y];
    else if((x<0) && (y<0)) color=0;
    else if((0<=y) && (y<LEN) && (x<0)) color=1;
    else if((y>=LEN) && (x<0)) color=2;
    else if((y>=LEN) && (0<=x) && (x<LEN)) color=3;
    else if((y>=LEN) && (x>=LEN)) color=4;
    else if((0<=y) && (y<LEN) && (x>=LEN)) color=5;
    else if((y<0) && (x>=LEN)) color=6;
    else if((y<0) && (0<=x) && (x<LEN)) color=7;
    return color;
}

int fill_pic(int x,int y,int color,int i_color){
    if((0<=x) && (x<LEN) && (0<=y) && (y<LEN)) pic[x][y]=color;
    else return 0;
    if((0<=y-1) && (y-1<LEN)){
        int W=pic[x][y-1];
        if(W==i_color) fill_pic(x,y-1,color,i_color);
        else ;
    }
    else ;
    if((0<=x+1) && (x+1<LEN) && (0<=y-1) && (y-1<LEN)){
        int SW=pic[x+1][y-1];
        if(SW==i_color) fill_pic(x+1,y-1,color,i_color);
        else ;
    }
    else ;
    if((0<=x-1) && (x-1<LEN) && (0<=y-1) && (y-1<LEN)){ 
        int NW=pic[x-1][y-1];   
        if(NW==i_color) fill_pic(x-1,y-1,color,i_color);
        else ;
    }
    else ;
    if((0<=y) && (y<LEN)){
        int E=pic[x][y+1];
        if(E==i_color) fill_pic(x,y+1,color,i_color);
        else ;
    }
    else ;
    if((0<=x+1) && (x+1<LEN) && (0<=y+1) && (y+1<LEN)){
        int SE=pic[x+1][y+1];    
        if(SE==i_color) fill_pic(x+1,y+1,color,i_color);
        else ;
    }
    else ;
    if((0<=x-1) && (x-1<LEN) && (0<=y+1) && (y+1<LEN)){
        int NE=pic[x-1][y+1];    
        if(NE==i_color) fill_pic(x-1,y+1,color,i_color);
        else ;
    }
    else ;
    if((0<=x+1) && (x+1<LEN)){
        int S=pic[x+1][y];
        if(S==i_color) fill_pic(x+1,y,color,i_color);
        else ;
    }
    else ;
    if((0<=x-1) && (x-1<LEN)){
        int N=pic[x-1][y];
        if(N==i_color) fill_pic(x-1,y,color,i_color);
        else ;
    }
    else ;    
    return 0;
}

int copy_paste(int cr1,int cc1,int cr2,int cc2,int pr1,int pc1,int pr2,int pc2){
    int color_copy,color_paste;
    int b_cr= cr1>cr2 ? cr1:cr2; int s_cr= cr1<cr2 ? cr1:cr2; 
    int b_cc= cc1>cc2 ? cc1:cc2; int s_cc= cc1<cc2 ? cc1:cc2;
    int s_pr= pr1<pr2 ? pr1:pr2; int s_pc= pc1<pc2 ? pc1:pc2;
    int diff_c= (s_pc-s_cc); int diff_r= (s_pr-s_cr);

    for(i=s_cr; i <= b_cr; ++i){
        for(j=s_cc; j <= b_cc; ++j){
            color_copy= pic[i][j];
            color_paste= pic[i+(diff_r)][j+(diff_c)];
            if(color_paste!=color_copy){
                pic[i+(diff_r)][j+(diff_c)]=pic[i][j];
                ++change;
            } 
            else continue;
        }    
    }
    return 0; 
}

int rotate(int sr,int sc,int len,int arr[][LEN/2]){
    for(i=0;i<=len;i++){
        for(j=0;j<=len;j++){
            arr[len-j][i]=matrix[i][j];
            
        }
    }
    for(i=0;i<=len;i++){
        for(j=0;j<=len;j++){
            matrix[i][j]=arr[i][j];
        }
    }   
    return 0;
}
int rotating(int sr,int sc,int len,int mat[][LEN/2],int D){
    if(D==90) rotate(sr,sc,len,mat);
    else if(D==180){
       rotate(sr,sc,len,mat);
       rotate(sr,sc,len,mat);
    }
    else if(D==270){
        rotate(sr,sc,len,mat);
        rotate(sr,sc,len,mat);
        rotate(sr,sc,len,mat);
    }
    return 0;
}
int copy_array(int sr,int sc,int br,int bc,int D){
    int len=(br-sr);
    int c_mat[LEN/2][LEN/2];
    int psr,psc,pbr,pbc;
    for(i=sr;i<=br;i++){
        for(j=sc;j<=bc;j++){
            matrix[i-sr][j-sc]=pic[i][j];
            c_mat[i-sr][j-sc]=pic[i][j];
        }
    }
    if(D>0) rotating(sr,sc,len,c_mat,D);
    else ;
    scanf("%d %d %d %d",&psr,&psc,&pbr,&pbc);
    for(x=psr; x <= pbr; x++){
        for(y=psc; y <= pbc; y++){
            if(pic[x][y]!=c_mat[x-psr][y-psc]){
            pic[x][y]=c_mat[x-psr][y-psc];
            change++;
            }
        }
    }
    return 0;
}