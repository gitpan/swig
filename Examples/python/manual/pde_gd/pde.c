#include "pde.h"


/* Grid Functions */

Grid2d::Grid2d(int ni, int nj) {
  int i,j;
  xpoints = ni;
  ypoints = nj;
  data = new double *[ni];
  for (i = 0; i < ni; i++)
    data[i] = new double[nj];

  for (i = 0; i < xpoints; i++)
    for (j = 0; j < ypoints; j++)
      data[i][j] = 0.0;
}

Grid2d::~Grid2d() {
  for (int i = 0; i < xpoints; i++) {
    delete data[i];
  }
  delete data;
}

/* Heat2d methods */

Heat2d::Heat2d(int ni, int nj) {
  work = new Grid2d(ni+1,nj+1);
  grid = new Grid2d(ni+1,nj+1);
  
  // Set a few parameters here

  h = 1.0/ni;
  k = 1.0/nj;
  time = 0.0;
  // Pick a safe value of 'dt'
  dt = 0.125*1.0/(1.0/(h*h) + 1.0/(k*k));

}

/* Clean up */

Heat2d::~Heat2d() {
  delete grid;
  delete work;
}

/* Solve equations for a few timesteps */

void Heat2d::solve(int nsteps) {
  double s,r, **u, **w;
  int i,j,n;
  Grid2d  *temp;

  r = dt/(h*h);
  s = dt/(k*k);
  
  if (r+s >= 0.5) {
    printf("Warning : Unstable solution.\n");
  }

  for (n = 0; n < nsteps; n++) {
    w = work->data;
    u = grid->data;
    for (i = 1; i < grid->xpoints-1; i++)
      for (j = 1; j < grid->ypoints-1; j++) {
	w[i][j] = (1.0-2*(r+s))*u[i][j] + r*(u[i+1][j] + u[i-1][j]) +
	  s*(u[i][j+1] + u[i][j-1]);
      }
    
    // Copy boundary points over

    for (i = 0; i < grid->xpoints; i++) {
      w[i][0] = u[i][0];
      w[i][grid->ypoints-1] = u[i][grid->ypoints-1];
    }
    for (i = 0; i < grid->ypoints; i++) {
      w[0][i] = u[0][i];
      w[grid->xpoints-1][i] = u[grid->xpoints-1][i];
    }
    
    time += dt;

    // Swap working and current data

    temp = work;
    work = grid;
    grid = temp;
  }
}

void Heat2d::set_temp(double temp) {
  int i,j;
  for (i = 0; i < grid->xpoints; i++)
    for (j = 0; j < grid->ypoints; j++)
      grid->data[i][j] = temp;
}

  
