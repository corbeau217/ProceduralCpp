

class Tile{
    public:
    //constructor
    Tile(char *nameIn)
        :tileName{nameIn}{}
    //destructor
    ~Tile(){

    }
    private:
    char *tileName;
};