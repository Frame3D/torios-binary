#include "functions.h"
std::string get_type(std::string fname)
{
  std::vector<std::string> Syntax_Headers=get_syntax_headers();
  if(!test_file(fname))
  {
    trace("No file sent in\n"+fname);
    return "";
  }
  
  std::string ext;
  
  unsigned int dot = fname.rfind(".");
  if(dot<fname.length())
  {
    std::string tmp=fname;
    tmp=tmp.substr(dot,std::string::npos);
    ext=tmp;
  }
  std::string tmp = syntax_type_from_filename(fname);
  if (tmp.compare("")!=0)
    return tmp;
  /// get the shebang
  std::string thisLine;
  std::ifstream inputFileStream(fname.c_str(), std::ifstream::in);
  if(inputFileStream.is_open())
  {
    getline(inputFileStream,thisLine);
  }
  
  // shell scripts don't always constain an extention... but the shebang tells
  if(thisLine.find("#!")==0)
  {
    std::string tmp=thisLine;
    unsigned int find = tmp.rfind("/");
    if(find<tmp.length())
    {
      tmp=tmp.substr(find+1,std::string::npos);
      tmp="."+tmp;
      ext=tmp;
    }
  }
  if( (thisLine.find("<?xml")<thisLine.length()))
  {
    for( std::vector<std::string>::iterator itr = Syntax_Headers.begin();
                                                itr!=Syntax_Headers.end();
                                                ++itr)
    {
      std::string tmp=*itr;
      std::string c="."+tmp;
      if(c.compare(ext)==0)
      {
        return tmp;
        
      }
    }
    ext="xml";
  }
  if(thisLine.find("<!DOCTYPE html>")<thisLine.length())
  {
    ext="html";
  }
  //nothing?  lets leave then...
  if(ext.compare("")==0)
    return "";
  
  std::string EXT = ext;
  std::transform(EXT.begin(), EXT.end(), EXT.begin(), ::tolower);
  unsigned int f_dot = EXT.find(".");
  if(f_dot < EXT.length())
  {
    EXT = EXT.substr(f_dot+1,std::string::npos);
  }
  //get the syntax highlighter file
  std::string filename = get_syntax_file();

  if(filename.compare("")==0){return "";}
  
  //this is the line we are looking for
  std::string line = "ext=";
  
  //parse the syntax highlighter file
  std::ifstream inputFileStrem (filename.c_str(), std::ifstream::in);
  /** check if the input file stream is open */
  if(inputFileStrem.is_open())
  {
    std::string this_line;
    std::string HEADER = "";
    while (getline(inputFileStrem,this_line))
    {
      
      if(this_line.find("[") <= 1)
      {
         unsigned int open_bracket =  this_line.find("[");
         unsigned int close_bracket = this_line.find("]");
         HEADER=this_line.substr(open_bracket+1,close_bracket-1);
      }
      unsigned int eq = this_line.find("=");
      if(this_line.find("filename=")<this_line.length())
      {
        std::string temp_fname = fname;
        std::transform(temp_fname.begin(), temp_fname.end(), temp_fname.begin(), ::tolower);
        this_line=this_line.substr(eq+1,std::string::npos);
        std::vector<std::string> V = make_vec(this_line,",");
        for( std::vector<std::string>::iterator itr = V.begin();
                                                itr!=V.end();
                                                ++itr)
        {
          std::string tmp=*itr;
          std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
          if(tmp.compare(fname)==0)
            return HEADER;
        }
      }
  
      if(this_line.find(line)<this_line.length())
      {
        this_line=this_line.substr(eq+1,std::string::npos);
        std::vector<std::string> V = make_vec(this_line,",");
        for( std::vector<std::string>::iterator itr = V.begin();
                                                itr!=V.end();
                                                ++itr)
        {
          std::string tmp=*itr;
          std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
          if(tmp.compare(EXT)==0)
            return HEADER;
        }
      }
    }
  }
  
  if(EXT.compare("bash")==0)
    return "sh";
  return "";
}
