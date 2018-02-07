#ifndef FILEREADER_H
# define FILEREADER_H

# include <stdint.h>
# include <fstream>
# include <vector>
# include <string>

class dice{
  private:
  int sides;
  int base;
  int count;
public:
  dice()  
  {
  }
  dice(int b, int c, int s) : sides(s), base(b), count(c)
  {
    //anything in here ??
  }
  int roll() const
  {
    return 0;
  }
};

class mob_description {
  public:
    std::vector<std::string> color;
    dice hp;
    dice attack;
    dice speed;
    std::string name;
    std::string descrption;
    char symbol;
    std::vector<std::string>  abilities;
};

std::vector<mob_description> read_file(std::string file_name);




#endif
