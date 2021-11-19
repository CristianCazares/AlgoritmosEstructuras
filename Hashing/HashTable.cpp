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

        //Hash function.
        int genHash(int key){
            return key % size;
        }


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
                        iaux = (pos + collisions*collisions);
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
    /*=Test 1
      Example provided by M.C. Luis Ricardo Peña Llamas: */
    cout << "Test 1:"
    Hash hash(11);
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
    hash.showTable();
    cout << endl << endl;

    /*=TEST 2
      Quadratic prove example from Geeks for geeks: https://media.geeksforgeeks.org/wp-content/uploads/20200421211818/Hashing3.png*/
    cout << "Test 2:"
    Hash hash1(7);
    hash1.insertQuadratic(50);
    hash1.showTable();
    hash1.insertQuadratic(700);
    hash1.insertQuadratic(76);
    hash1.showTable();
    hash1.insertQuadratic(85);
    hash1.showTable();
    hash1.insertQuadratic(92);
    hash1.showTable();
    hash1.insertQuadratic(73);
    hash1.insertQuadratic(101);
    hash1.showTable();
    /*
    */
    /*
    hash.insertChain(17);
    hash.insertChain(7);
    hash.insertChain(6);
    hash.insertChain(28);
    hash.insertChain(52);
    hash.insertChain(76);
    hash.insertChain(35);
    hash.insertChain(9);
    hash.insertChain(78);
    hash.insertChain(68);*/

    return 0;
}
