/* Data structure for holding longitude and lattitude information */

typedef struct Location {
  char    *name;
  double  lat_degrees;
  double  lat_minutes;
  double  lat_seconds;
  char    lat_direction;
  double  long_degrees;
  double  long_minutes;
  double  long_seconds;
  char    long_direction;
} Location;

extern Location *new_Location(char *name);



