/*
    Author: Cristian Javier Cázares Molina
    Date:   November 12th 2021
    
    Hashing by inserting using chaining and quadratic probing
*/
#include <iostream>
#include <vector>
using namespace std;

class Hash{
    public: 
        int size;
        int inserted = 0; //Register of occupied indexes to avoid unnecessary insertions
        vector<int> table;
        Hash(int Size){
            size = Size;
            vector<int> aux;
            table = vector<int>(size);
        }

        //Hash function. For demonstration purposes prints the key and the hash generates.
        int genHash(int key){
            cout << "  H(" << key << ")=" << key % size <<  " " << endl;
            return key % size;
        }
        //Discrete alternative for Hash function. Does not print.
        int genHashDiscrete(int key){
            return key % size;
        }

        //Complexity: O(n)
        void insertChain(int key){
            //Insert to hash if it is not full
            if(inserted < size){
                int pos = genHash(key);
                /*
                The position of the new key will be the result of the hash function.
                That positions is very likely to be occupied, so an iterator is needed
                 to start from that position and go around the vector.
                To do that we need the iterator to go from position to (position + size).

                For example, if the start position is 5 in a vector of size 7, we expect to
                 go all around the vector, where index = 7 is the in reality the first element
                 of the array:
                  0 1 2 3  4  5  6
                  ^ ^ ^ ^  ^  ^  ^
                  7 8 9 10 11 12 13
                Therefor, starting on 5, to go all around the vector we need to stop at 11:
                 position + size = 5 + 6 = 11

                Nevertheless vectors does not work this way, the iterator must increase 11 times,
                 but once it reaches the size of the vector (6), the next iterator must be 0.
                That's why we use a for loop from position to size + position, but we subtract
                 size when that addition is greater than the size:
                    if(  iterator   >= size): iterator -= size
                    if((size + pos) >= size): iterator -= size
                    if(      6      >=  6  ): iterator -= 6 = 0  <-(begining of vector)
                */
                for(int i = pos; i < size+pos; i++){
                    int iaux = i;
                    if(iaux >= size){
                        iaux -= size;
                    }
                    if(!table[iaux]){
                        table[iaux] = key;
                        inserted++;
                        return;
                    }
                }
            }else{
                cout << "Hash full!" << endl;
            }
        }

        //Complexity: O(n)
        void insertQuadratic(int key){
            vector<bool> visited(size, false); //Keep track of visited index.


            //Insert to hash if it is not full
            if(inserted < size){
                int pos = genHash(key), iaux = pos;
                bool collisioned = false; 
                int collisions = 0; 

                /*Quadratic collisions formula used:
                    new index to check collision = hash function + (collisions detected)^2*/

                for(int i = pos; i < size+pos; i++){
                    /*If the iterator is grater than the size, we need to go back
                    to the beggining of the vector: iterator -= vector size*/
                    if(iaux >= size){
                        iaux -= size;
                    }
                    
                    //If it the last index was collided, move to the next one.
                    if(collisioned){
                        iaux = (genHashDiscrete(pos + collisions*collisions));
                        collisioned = false;
                    } //(Never applies for the first try)
                    
                    //If position is null, there is no collision, proceed to insert.
                    if(!table[iaux]){
                        table[iaux] = key;
                        inserted++;
                        return;
                    }else{
                        //A collision was detected.

                        //If position was already collided, we are on a loop
                        if(visited[iaux]){
                            cout << "Could not insert. The generated hash always collides." << endl;
                            return;
                        }

                        /*If it was the first time colliding, update variables that keep track
                         of past collitions*/
                        visited[iaux] = true;
                        collisioned = true;
                        collisions++;
                    }
                }
            }else{
                cout << "Hash full!" << endl;
            }
        }


        void showTable(){
            for(int i = 0; i < table.size(); i++){
                cout << table[i] << " ";
            }
            cout << endl;
        }
};

int main(){
    /*Test 1 CHAIN
      Fisrt 7 elements of example provided by M.C. Luis Ricardo Peña Llamas:
        https://raw.githubusercontent.com/CristianCazares/AlgoritmosEstructuras/main/Hashing/img/Test1.png*/
    cout << "===Test 1:" << endl;
    Hash hash(11);
    cout << " Keys to insert: " << endl;
    hash.insertChain(33);
    hash.insertChain(17);
    hash.insertChain(7);
    hash.insertChain(6);
    hash.insertChain(28);
    hash.insertChain(52);
    hash.insertChain(76);
    hash.insertChain(35);
    hash.insertChain(9);
    hash.insertChain(78);
    hash.insertChain(68);
    cout << "Result:" << endl;
    hash.showTable();
    cout << endl << endl;

    /*Test 2 QUADRATIC.
      Same as test 1 but using quadratic.
    */
    cout << "===Test 2:" << endl;
    Hash hash2(11);
    cout << " Keys to insert: " << endl;
    hash2.insertQuadratic(33);
    hash2.insertQuadratic(17);
    hash2.insertQuadratic(7);
    hash2.insertQuadratic(6);
    hash2.insertQuadratic(28);
    hash2.insertQuadratic(52);
    hash2.insertQuadratic(76);
    hash2.insertQuadratic(35);
    hash2.insertQuadratic(9);
    hash2.insertQuadratic(78);
    hash2.insertQuadratic(68);
    cout << "Result:" << endl;
    hash2.showTable();
    cout << endl << endl;


    /*Test 3 QUADRATIC
      Quadratic prove example from Geeks for geeks:
        https://media.geeksforgeeks.org/wp-content/uploads/20200421211818/Hashing3.png*/
    cout << "===Test 3:" << endl ;
    Hash hash3(7);
    cout << " Keys to insert: " << endl;
    hash3.insertQuadratic(50);
    hash3.insertQuadratic(700);
    hash3.insertQuadratic(76);
    hash3.insertQuadratic(85);
    hash3.insertQuadratic(92);
    hash3.insertQuadratic(73);
    hash3.insertQuadratic(101);
    cout << "Result:" << endl;
    hash3.showTable();
    cout << endl << endl;


    /*Test 4 CHAIN.
      Same as test 3 but using chain.
    */
    cout << "===Test 4:" << endl ;
    Hash hash4(7);
    cout << " Keys to insert: " << endl;
    hash4.insertChain(50);
    hash4.insertChain(700);
    hash4.insertChain(76);
    hash4.insertChain(85);
    hash4.insertChain(92);
    hash4.insertChain(73);
    hash4.insertChain(101);
    cout << "Result:" << endl;
    hash4.showTable();

    return 0;
}