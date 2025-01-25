-For Compilation
g++ -o project2_encryption project2_encryption.cpp -I/opt/homebrew/opt/openssl@3/include -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto
g++ -o project2_decryption project2_decryption.cpp -I/opt/homebrew/opt/openssl@3/include -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto


-For Execution
./project2_encryption symm_key.bin pubkey.pem privatekey.pem 
./project2_decryption signedcipher public.pem symmetric.txt 


-Password
vivek
