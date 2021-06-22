/*
 * Loco Wifi Control
 * 
 * file name class
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */


struct FILEINFO {
  String path;
  String filename;
  String extension;
};


class FileInfo {

  public:
    String path (String);
    String filename (String);
    String extension (String);
    String mime (String);
    FILEINFO split (String);

  private:
    FILEINFO _info;
    
};

