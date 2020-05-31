#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main (void) {
	int dataSets=0, aSize=0, bSize=0, t=0, ws=0, serve=0, prevServe=0, aScore=0, bScore=0;
	int side[4]={0};
	int cur=0;
	int newServe=0;
	int debug=0;
	int current[4];
	fstream fs;

	fs.open("ball.in", fstream::in);
	fs >> dataSets;

	for (int i=0; i<dataSets; i++) {
		fs >> aSize >> bSize >> t;
		side[0]=0;
		side[1]=0;
		side[2]=0;
		side[3]=0;
		current[0]=0;
		current[1]=0;
		current[2]=0;
		current[3]=0;
		serve=0;
		prevServe=0;
		aScore=0;
		bScore=0;
		newServe=0;
		ws=0;



		for (int j=0; j<t; j++) {
			current[3]=current[2];
			current[2]=current[1];
			current[1]=current[0];
	
				if (fs.peek()==' ') fs.get();
				if (fs.peek()=='A') {
					current[0]=-1;
					fs.get();
				}
				else if (fs.peek()=='B') {
					current[0]=-2;
					fs.get();
				}
				else if (fs.peek()=='X') {
					current[0]=-3;
					fs.get();
				}
				else {
					fs >> current[0];
				}
			
			side[3]=side[2];
			side[2]=side[1];
			side[1]=side[0];


			stringstream ss;
			ss<<current[0];
			ss>>cur;


			if (current[0]==-1) side[0]=0;
			else if (current[0]==-2) side[0]=0;
			else if (current[0]==-3) side[0]=0;
			else {
				if (cur<=aSize) side[0]=1;
				else side[0]=2;
			}

			if (j==0) serve=side[0];

			// Wrong side serves
			if (newServe==0) {
				if (side[0]==1 && serve==2) {
					ws=1;
					if (debug==1) cout << "\n" << j << ": WS";
				}
				else if (side[0]==2 && serve==1) {
					ws=1;
					if (debug==1) cout << "\n" << j << ": WS";
				}
			}

			// Same side hits ball after serve
			if (side[0]==1 && serve==1 && newServe==1) {
				newServe=0;
				serve=2;
				if (debug==1) cout << "\n" << j << ": Same side hit ball after serve\n";
			}
			else if (side[0]==2 && serve==2 && newServe==1) {
				newServe=0;
				serve=1;
				if (debug==1) cout << "\n" << j << ": Same side hit ball after serve\n";
			}
			
			// Ball hits ground in bounds
			else if (current[0]==-1) {
				if (serve==2) bScore++;
				newServe=0;
				serve=2;
				if (debug==1) cout << "\n" << j << ": Ball hit ground in bounds\n";
			}
			else if (current[0]==-2) {
				if (serve==1) aScore++;
				newServe=0;
				serve=1;
				if (debug==1) cout << "\n" << j << ": Ball hit ground in bounds\n";
			}

			// Ball hits ground out of bounds
			else if (side[1]==1 && current[0]==-3) {
				if (serve==2) bScore++;
				newServe=0;
				serve=2;
				if (debug==1) cout << "\n" << j << ": Ball hit ground out of bounds\n";
			}
			else if (side[1]==2 && current[0]==-3) {
				if (serve==1) aScore++;
				newServe=0;
				serve=1;
				if (debug==1) cout << "\n" << j << ": Ball hit ground out of bounds\n";
			}

			// Same person hits ball twice in a row
			else if (current[1]==current[0] && current[1]!=-1 && current[1]!=-2 && current[1]!=-3) {
				if (side[0]==2) {
					if (serve==1) aScore++;
					newServe=0;
					serve=1;
					if (debug==1) cout << "\n" << j << ": Same person hit ball twice\n";
				}
				else if (side[0]==1) {
					if (serve==2) bScore++;
					newServe=0;
					serve=2;
					if (debug==1) cout << "\n" << j << ": Same person hit ball twice\n";
				}
			}

			// Same side hits ball four times in a row
			else if (side[3]==side[2] && side[3]==side[1] && side[3]==side[0]) {
				if (side[0]==2) {
					if (serve==1) aScore++;
					newServe=0;
					serve=1;
					if (debug==1) cout << "\n" << j << ": Same side hit ball four times\n";
				}
				else if (side[0]==1) {
					if (serve==2) bScore++;
					newServe=0;
					serve=2;
					if (debug==1) cout << "\n" << j << ": Same side hit ball four times\n";
				}
			}
			else {
				newServe++;
			}
		}
		
		cout << "Data Set " << i+1 << ":" << endl;
		if (ws==0) {
			cout << aScore << " " << bScore <<endl;
		}
		else {
			cout << "Wrong Serve" << endl;
		}

	}

}