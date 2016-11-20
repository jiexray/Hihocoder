/*
 * Author: Xia Rui
 * Problem: Hihocoder week 125
*/

#include <iostream>
#include <string>
#include <utility>
#include <iomanip>
#define CODE_LEN 10
#define PRECISION (CODE_LEN*5)

using namespace std;

int n, m;
double loc_x[110];
double loc_y[110];
string codes[110];
char base32[] = {'0','1','2','3','4','5','6','7','8','9','b','c','d','e','f', 
					'g','h','j','k','m','n','p','q','r','s','t','u','v','w','x','y','z'};


void solve();
string encode(double x, double y, int prec);
pair<double, double> decode(string code);
int getDec(char c){
	for(int i = 0; i < 32; i++)
		if(base32[i] == c)
			return i;
	return -1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("/Users/jiexray/Documents/work/OJ/Source/week125/in", "r", stdin);
#endif
	while(cin >> n >> m){
		for(int i = 0; i < n; i++){
			cin >> loc_x[i] >> loc_y[i];
		}
		for(int i = 0; i < m; i++){
			cin >> codes[i];
		}
		solve();
	}
	return 0;
}

void solve(){
	for(int i = 0; i < n; i++){
		string ans = encode(loc_x[i], loc_y[i], PRECISION);
		cout << ans << endl;
	}
	for(int i = 0; i < m; i++){
		pair<double, double> ans = decode(codes[i]);
		cout << fixed << setprecision(6) << ans.first << " " << ans.second << endl;
	}
}

string encode(double x, double y, int prec){
	double lat_low = -90.0, lat_high = 90.0;
	double lon_low = -180.0, lon_high = 180.0;
	string geohash = "";
	int bits = 0;
	for(int i =  1; i <= prec; i++){
		if(i % 2 == 1){
			// longitude
			double mid = (lon_low + lon_high) / 2.0;
			if(y > mid){
				bits = bits * 2 + 1;
				lon_low = mid;
			}else{
				bits = bits*2;
				lon_high = mid;
			}
		}else{
			// latitude
			double mid = (lat_low + lat_high) / 2.0;
			if(x > mid){
				bits = bits * 2 + 1;
				lat_low = mid;
			}else{
				bits = bits * 2;
				lat_high = mid;
			}
		}

		if(i % 5 == 0){
			geohash += base32[bits];
			bits = 0;
		}
	}
	return geohash;
}

pair<double, double> decode(string code){
	pair<double, double> ans;
	double lat_low = -90.0, lat_high = 90.0;
	double lon_low = -180.0, lon_high = 180.0;
	int prec = 5 * code.size();

	for(int i = 0; i < code.size(); i++){
		int bits = getDec(code[i]);
		for(int j = 5; j >= 1; j--){
			if(prec % 2 == 1){
				// latitude x
				double mid = (lat_low + lat_high) / 2.0;
				if((bits >> (j-1)) & 0x1){
					lat_low = mid;
				}else{
					lat_high = mid;
				}
			}else{
				// longitude y
				double mid = (lon_low + lon_high) / 2.0;
				if((bits >> (j-1)) & 0x1){
					lon_low = mid;
				}else{
					lon_high = mid;
				}
			}
			prec--;
		}
	}
	ans.first = (lat_low + lat_high) / 2.0;
	ans.second = (lon_low + lon_high) / 2.0;

	return ans;
}




