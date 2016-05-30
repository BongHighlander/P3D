#include "lib_3d.h"
#include "lib_mat.h"

void multiplicationVecteur3d(t_point3d *v1, double m[4][4], t_point3d *v2) // v1 = m*v2
{

	v1->xyzt[0] = m[0][0]*v2->xyzt[0] + m[0][1]*v2->xyzt[1] + m[0][2]*v2->xyzt[2] + m[0][3]*v2->xyzt[3];

	v1->xyzt[1] = m[1][0]*v2->xyzt[0] + m[1][1]*v2->xyzt[1] + m[1][2]*v2->xyzt[2] + m[1][3]*v2->xyzt[3];

	v1->xyzt[2] = m[2][0]*v2->xyzt[0] + m[2][1]*v2->xyzt[1] + m[2][2]*v2->xyzt[2] + m[2][3]*v2->xyzt[3];

	v1->xyzt[3] = m[3][0]*v2->xyzt[0] + m[3][1]*v2->xyzt[1] + m[3][2]*v2->xyzt[2] + m[3][3]*v2->xyzt[3];

}

void multiplicationMatrice3d(double m1[4][4], double m2[4][4], double m3[4][4]) // m1 = m2*m3
{
    int i,j,k;
	for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
                m1[i][j] = 0;
            for(k=0;k<4;k++) {
                m1[i][j] = m1[i][j] + m2[i][k]*m3[k][j];
            }
        }
	}


}

void copierMatrice3d(double m1[4][4], double m2[4][4]) // m1 = m2
{
    int i,j;
	for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            m1[i][j] = m2[i][j];
        }
	}
}
