/*
* 三角形:
* 1. 半周长 P=(a+b+c)/2
* 2. 面积 S=aHa/2=absin(C)/2=sqrt(P(P-a)(P-b)(P-c))
* 3. 中线 Ma=sqrt(2(b^2+c^2)-a^2)/2=sqrt(b^2+c^2+2bccos(A))/2
* 4. 角平分线 Ta=sqrt(bc((b+c)^2-a^2))/(b+c)=2bccos(A/2)/(b+c)
* 5. 高线 Ha=bsin(C)=csin(B)=sqrt(b^2-((a^2+b^2-c^2)/(2a))^2)
* 6. 内切圆半径 r=S/P=asin(B/2)sin(C/2)/sin((B+C)/2)
*                =4Rsin(A/2)sin(B/2)sin(C/2)=sqrt((P-a)(P-b)(P-c)/P)
*                =Ptan(A/2)tan(B/2)tan(C/2)
* 7. 外接圆半径 R=abc/(4S)=a/(2sin(A))=b/(2sin(B))=c/(2sin(C))
* 
* 四边形:
* D1,D2为对角线,M对角线中点连线,A为对角线夹角
* 1. a^2+b^2+c^2+d^2=D1^2+D2^2+4M^2
* 2. S=D1D2sin(A)/2
* (以下对圆的内接四边形)
* 3. ac+bd=D1D2
* 4. S=sqrt((P-a)(P-b)(P-c)(P-d)),P为半周长
* 
* 正n边形:
* R为外接圆半径,r为内切圆半径
* 1. 中心角 A=2PI/n
* 2. 内角 C=(n-2)PI/n
* 3. 边长 a=2sqrt(R^2-r^2)=2Rsin(A/2)=2rtan(A/2)
* 4. 面积 S=nar/2=nr^2tan(A/2)=nR^2sin(A)/2=na^2/(4tan(A/2))
* 
* 圆:
* 1. 弧长 l=rA
* 2. 弦长 a=2sqrt(2hr-h^2)=2rsin(A/2)
* 3. 弓形高 h=r-sqrt(r^2-a^2/4)=r(1-cos(A/2))=atan(A/4)/2
* 4. 扇形面积 S1=rl/2=r^2A/2
* 5. 弓形面积 S2=(rl-a(r-h))/2=r^2(A-sin(A))/2
* 
* 棱柱:
* 1. 体积 V=Ah,A为底面积,h为高
* 2. 侧面积 S=lp,l为棱长,p为直截面周长
* 3. 全面积 T=S+2A
* 
* 棱锥:
* 1. 体积 V=Ah/3,A为底面积,h为高
* (以下对正棱锥)
* 2. 侧面积 S=lp/2,l为斜高,p为底面周长
* 3. 全面积 T=S+A
* 
* 棱台:
* 1. 体积 V=(A1+A2+sqrt(A1A2))h/3,A1.A2为上下底面积,h为高
* (以下为正棱台)
* 2. 侧面积 S=(p1+p2)l/2,p1.p2为上下底面周长,l为斜高
* 3. 全面积 T=S+A1+A2
*
* 圆柱:
* 1. 侧面积 S=2PIrh
* 2. 全面积 T=2PIr(h+r)
* 3. 体积 V=PIr^2h
* 
* 圆锥:
* 1. 母线 l=sqrt(h^2+r^2)
* 2. 侧面积 S=PIrl
* 3. 全面积 T=PIr(l+r)
* 4. 体积 V=PIr^2h/3
* 
* 圆台:
* 1. 母线 l=sqrt(h^2+(r1-r2)^2)
* 2. 侧面积 S=PI(r1+r2)l
* 3. 全面积 T=PIr1(l+r1)+PIr2(l+r2)
* 4. 体积 V=PI(r1^2+r2^2+r1r2)h/3
* 
* 球:
* 1. 全面积 T=4PIr^2
* 2. 体积 V=4PIr^3/3
* 
* 球台:
* 1. 侧面积 S=2PIrh
* 2. 全面积 T=PI(2rh+r1^2+r2^2)
* 3. 体积 V=PIh(3(r1^2+r2^2)+h^2)/6
* 
* 球扇形:
* 1. 全面积 T=PIr(2h+r0),h为球冠高,r0为球冠底面半径
* 2. 体积 V=2PIr^2h/3
*/