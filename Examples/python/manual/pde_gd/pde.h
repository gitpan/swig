
#include <math.h>
#include <stdio.h>

/* A simple 2D Grid structure */

struct Grid2d {
  Grid2d(int ni, int nj);
  ~Grid2d();
  double **data;
  int      xpoints;
  int      ypoints;
};

/* Here's a class for solving a simple heat equation */

class Heat2d {
private:
  Grid2d    *work;                    // Temporary grid, needed for solver
  double    h,k;
public:    
  Heat2d(int ni, int nj); 
  ~Heat2d();
  Grid2d    *grid;                    // Data
  double     dt;                      // Timestep
  double     time;					
  void       solve(int nsteps);       // Run for nsteps
  void       set_temp(double temp);   // Set temperature
};

