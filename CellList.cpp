
#include "Cell.cpp"

const int MIN_SIZE {10};

class CellList{
    public:
    CellList()
        :elem{new Cell*[MIN_SIZE]},n{0},sz{MIN_SIZE},currIdx{0}{}
    CellList(int size)
        :elem{new Cell*[size]},n{0},sz{size},currIdx{0}{}
    ~CellList(){
        // we should revisit this, we might have cooked it doing this
        delete[] elem;
    }

    /**
     * @brief to check if our list is full
     * 
     * @return true if n==sz
     * @return false otherwise
     */
    bool isFull(){
        return n==sz;
    }
    
    /**
     * @brief expands the list size
     * 
     * overloaded to take an expand by parameter
     */
    void expand(){
        // add half the size plus 1
        //     (plus 1 incase we end up at 0)
        expand(sz/2+1);
    }
    void expand(int howMuch){
        // make a new list
        Cell* newList[sz+howMuch];
        for(int idx = 0; idx < sz; idx++){
            *newList[idx] = get(idx);
        }
        elem = newList;
        sz += howMuch;
    }
    
    /**
     * @brief getter member function
     * 
     * @param idx : index to get from 
     * @return Cell& : the cell from the list
     */
    Cell& get(int idx){
        return *elem[idx];
    }
    void add(Cell& cell){
        if(isFull())
            expand();
        *elem[n++] = cell;
    }

    bool hasNext(){
        return currIdx<n;
    }
    Cell& next(){
        return get(currIdx++);
    }
    
    private:
    Cell** elem;
    int n;
    int sz;
    
    int currIdx;
};