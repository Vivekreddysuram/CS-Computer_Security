	#include <iostream>
	#include <vector>
	#include <string>

	using namespace std;

	vector<int> stringToVector(const string& binaryString) {
	    vector<int> bits;
	    for (char c : binaryString) {
		bits.push_back(c - '0');
	    }
	    return bits;
	}

	int majority(int x, int y, int z) {
	    return (x + y + z > 1) ? 1 : 0;
	}

	void stepX(vector<int>& X) {
	    int t = X[13] ^ X[16] ^ X[17] ^ X[18];
	    X.insert(X.begin(), t); 
	    X.pop_back(); 
	}


	void stepY(vector<int>& Y) {
	    int t = Y[20] ^ Y[21];
	    Y.insert(Y.begin(), t);
	    Y.pop_back();
	}


	void stepZ(vector<int>& Z) {
	    int t = Z[7] ^ Z[20] ^ Z[21] ^ Z[22];
	    Z.insert(Z.begin(), t);
	    Z.pop_back();
	}

	int main() {
	    vector<int> X = stringToVector("1010010011000011100");
	    vector<int> Y = stringToVector("0011011100100001111011");
	    vector<int> Z = stringToVector("11101010001110111000010");
	    
	    string keystream;
	    
	    for (int i = 0; i < 32; ++i) {
		int m = majority(X[8], Y[10], Z[10]);
		if (X[8] == m) stepX(X);
		if (Y[10] == m) stepY(Y);
		if (Z[10] == m) stepZ(Z);
		
		int keystreamBit = X[18] ^ Y[21] ^ Z[22];
		keystream += to_string(keystreamBit);
	    }
	    

	    string finalX, finalY, finalZ;
	    for (int bit : X) finalX += to_string(bit);
	    for (int bit : Y) finalY += to_string(bit);
	    for (int bit : Z) finalZ += to_string(bit);
	    
	    cout << "Keystream (32 bits): " << keystream << endl;
	    cout << "Final state of X: " << finalX << endl;
	    cout << "Final state of Y: " << finalY << endl;
	    cout << "Final state of Z: " << finalZ << endl;
	    
	    return 0;
	}
