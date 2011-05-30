/**
 * Structure to keep calculation data
 */
struct DataStruct {
    // task specific data = will be moved to example implementation
    int x;
    int y;

    DataStruct(int arg1, int arg2) : x(arg1), y(arg2) {
    };

    /**
     * Copy constructor - necessary!
     */
    DataStruct(const DataStruct & ds) : x(ds.x), y(ds.y) {
    };

    DataStruct() {
    };

    /**
     * Function used in serialization proces;
     * It's sufficient to list all structure's fields in format:
     * ar & fieldName1;
     * ar & fieldName2;
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // task specific data = will be moved to example implementation
        ar & x;
        ar & y;
    }
};
