/**
 * Struktura do przechowywania wyników
 */
struct DataStruct
{
 int x;
 int y;

 DataStruct(int arg1, int arg2):  x(arg1), y(arg2) {};
 DataStruct(const DataStruct& ds): x(ds.x), y(ds.y) {};
 DataStruct() {};

 template<class Archive>
 void serialize (Archive & ar, const unsigned int version)
 {
  ar & x;
  ar & y;
 }
};
