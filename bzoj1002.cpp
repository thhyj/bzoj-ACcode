
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define DIGIT 1000000000
using namespace std;
string a[101];
int main()
{
	a[1]="1";
a[2]="5";
a[3]="16";
a[4]="45";
a[5]="121";
a[6]="320";
a[7]="841";
a[8]="2205";
a[9]="5776";
a[10]="15125";
a[11]="39601";
a[12]="103680";
a[13]="271441";
a[14]="710645";
a[15]="1860496";
a[16]="4870845";
a[17]="12752041";
a[18]="33385280";
a[19]="87403801";
a[20]="228826125";
a[21]="599074576";
a[22]="1568397605";
a[23]="4106118241";
a[24]="10749957120";
a[25]="28143753121";
a[26]="73681302245";
a[27]="192900153616";
a[28]="505019158605";
a[29]="1322157322201";
a[30]="3461452808000";
a[31]="9062201101801";
a[32]="23725150497405";
a[33]="62113250390416";
a[34]="162614600673845";
a[35]="425730551631121";
a[36]="1114577054219520";
a[37]="2918000611027441";
a[38]="7639424778862805";
a[39]="20000273725560976";
a[40]="52361396397820125";
a[41]="137083915467899401";
a[42]="358890350005878080";
a[43]="939587134549734841";
a[44]="2459871053643326445";
a[45]="6440026026380244496";
a[46]="16860207025497407045";
a[47]="44140595050111976641";
a[48]="115561578124838522880";
a[49]="302544139324403592001";
a[50]="792070839848372253125";
a[51]="2073668380220713167376";
a[52]="5428934300813767249005";
a[53]="14213134522220588579641";
a[54]="37210469265847998489920";
a[55]="97418273275323406890121";
a[56]="255044350560122222180445";
a[57]="667714778405043259651216";
a[58]="1748099984655007556773205";
a[59]="4576585175559979410668401";
a[60]="11981655542024930675232000";
a[61]="31368381450514812615027601";
a[62]="82123488809519507169850805";
a[63]="215002084978043708894524816";
a[64]="562882766124611619513723645";
a[65]="1473646213395791149646646121";
a[66]="3858055874062761829426214720";
a[67]="10100521408792494338631998041";
a[68]="26443508352314721186469779405";
a[69]="69230003648151669220777340176";
a[70]="181246502592140286475862241125";
a[71]="474509504128269190206809383201";
a[72]="1242282009792667284144565908480";
a[73]="3252336525249732662226888342241";
a[74]="8514727565956530702536099118245";
a[75]="22291846172619859445381409012496";
a[76]="58360810951903047633608127919245";
a[77]="152790586683089283455442974745241";
a[78]="400010949097364802732720796316480";
a[79]="1047242260609005124742719414204201";
a[80]="2741715832729650571495437446296125";
a[81]="7177905237579946589743592924684176";
a[82]="18791999880010189197735341327756405";
a[83]="49198094402450621003462431058585041";
a[84]="128802283327341673812651951847998720";
a[85]="337208755579574400434493424485411121";
a[86]="882823983411381527490828321608234645";
a[87]="2311263194654570182037991540339292816";
a[88]="6050965600552329018623146299409643805";
a[89]="15841633607002416873831447357889638601";
a[90]="41473935220454921602871195774259272000";
a[91]="108580172054362347934782139964888177401";
a[92]="284266580942632122201475224120405260205";
a[93]="744219570773534018669643532396327603216";
a[94]="1948392131377969933807455373068577549445";
a[95]="5100956823360375782752722586809405045121";
a[96]="13354478338703157414450712387359637585920";
a[97]="34962478192749096460599414575269507712641";
a[98]="91532956239544131967347531338448885552005";
a[99]="239636390525883299441443179440077148943376";
a[100]="627376215338105766356982006981782561278125";
int n;
cin>>n;
cout<<a[n];
}
