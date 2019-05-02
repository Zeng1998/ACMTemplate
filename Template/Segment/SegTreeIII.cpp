//注意标记下传的顺序
//lson rson同理，这里省略一个
void PushDown(int i){
    //set优先级最高(假设存在多种标记，set肯定是先来的，如果是后来的就会把mul和add覆盖)
    if(Set[i]){
        Set[lson]=Set[rson]=Set[i];   Add[lson]=Add[rson]=0;   Mul[lson]=Mul[rson]=1;
        sum1[lson]=((ri[lson]-le[lson]+1)*Set[i])%MOD;
        sum2[lson]=((((ri[lson]-le[lson]+1)*Set[i])%MOD)*Set[i])%MOD;
        sum3[lson]=(((((ri[lson]-le[lson]+1)*Set[i])%MOD)*Set[i]%MOD)*Set[i])%MOD;
        Set[i]=0;
    }
    if(Mul[i]!=1){
        Mul[lson]=(Mul[lson]*Mul[i])%MOD;   Mul[rson]=(Mul[rson]*Mul[i])%MOD;
        Add[lson]=(Add[lson]*Mul[i])%MOD;   Add[rson]=(Add[rson]*Mul[i])%MOD;
        sum3[lson]=(((((sum3[lson]*Mul[i])%MOD)*Mul[i])%MOD)*Mul[i])%MOD;
        sum2[lson]=(((sum2[lson]*Mul[i])%MOD)*Mul[i])%MOD;
        sum1[lson]=(sum1[lson]*Mul[i])%MOD;
        Mul[i]=1;
    }
    if(Add[i]){
        Add[lson]=(Add[lson]+Add[i])%MOD;   Add[rson]=(Add[rson]+Add[i])%MOD;
        sum3[lson]=(sum3[lson]+(3*sum2[lson]%MOD*Add[i]%MOD+(3*Add[i]%MOD*Add[i]%MOD
        *sum1[lson]%MOD+(Add[i]*Add[i]%MOD*Add[i]%MOD)*(ri[lson]-le[lson]+1))%MOD))%MOD;
        sum2[lson]=(sum2[lson]+(2*sum1[lson]%MOD*Add[i]%MOD
        +(Add[i]*Add[i])%MOD*(ri[lson]-le[lson]+1)))%MOD;
        sum1[lson]=(sum1[lson]+(ri[lson]-le[lson]+1)*Add[i]%MOD)%MOD;
        Add[i]=0;
    }
}
void Update(int i,int l,int r,int o,ll v){
    if(l<=le[i] && r>=ri[i]){
        if(o==1){
            //Add操作，更新Add标记
            Add[i]=(Add[i]+v)%MOD;
            //(a1^3+a2^3+...+an^3)==>((a1+v)^3+(a2+v)^3+...+(an+v)^3)==...化简
            sum3[i]=(sum3[i]+(3*sum2[i]%MOD*v%MOD+3*v%MOD*v%MOD*sum1[i]%MOD+v*v%MOD*v%MOD
            *(ri[i]-le[i]+1)%MOD))%MOD;
            //(a1^2+a2^2+...+an^2)==>((a1+v)^2+(a2+v)^2+...+(an+v)^2)==...化简
            sum2[i]=(sum2[i]+(2*sum1[i]*v%MOD+v*v%MOD*(ri[i]-le[i]+1)%MOD))%MOD;
            //(a1+a2+...+an)==>(a1+v+a2+v+...+an+v)=(a1+a2+...+an)+n*v
            sum1[i]=(sum1[i]+(ri[i]-le[i]+1)*v%MOD)%MOD;
        }else if(o==2){
            //Mul操作，更新Mul，Add标记
            Mul[i]=(Mul[i]*v)%MOD;
            Add[i]=(Add[i]*v)%MOD;
            sum3[i]=(((((sum3[i]*v)%MOD)*v)%MOD)*v)%MOD;
            sum2[i]=(((sum2[i]*v)%MOD)*v)%MOD;
            sum1[i]=(sum1[i]*v)%MOD;
        }else if(o==3){
            //Set操作，更新Set标记，覆盖Mul，Add标记
            Set[i]=v;
            Add[i]=0;
            Mul[i]=1;
            sum1[i]=((ri[i]-le[i]+1)*v)%MOD;
            sum2[i]=((((ri[i]-le[i]+1)*v)%MOD)*v)%MOD;
            sum3[i]=(((((ri[i]-le[i]+1)*v)%MOD)*v%MOD)*v)%MOD;
        }
        return;
    }
    //......
}