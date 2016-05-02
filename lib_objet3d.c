#include <assert.h>
#include <math.h>
#include "lib_3d.h"
#include "lib_objet3d.h"
#include "lib_mat.h"
#include "lib_surface.h"


// cree un nouveau maillon, cf cours algo
t_maillon* __cree_maillon(t_triangle3d *face2, Uint32 couleur2)
{
	t_maillon* pt_maillon = NULL;

	pt_maillon  = (t_maillon*) malloc(sizeof(t_maillon));
	/*Maillon est un pointeur sur liste 3d, à savoir :
	t_triangle3d *face;
    Uint32 couleur;
    t_maillon *pt_suiv; */

    pt_maillon->face = face2;
    pt_maillon->couleur = couleur2;



	return pt_maillon;
}

t_maillon* __copier_maillon(t_maillon *lol)
{
	t_maillon* pt_maillon = NULL;

	pt_maillon  = (t_maillon*) malloc(sizeof(t_maillon));
	/*Maillon est un pointeur sur liste 3d, à savoir :
	t_triangle3d *face;
    Uint32 couleur;
    t_maillon *pt_suiv; */

    pt_maillon->face = copierTriangle3d(lol->face);
    pt_maillon->couleur = lol->couleur;
    pt_maillon->pt_suiv = lol->pt_suiv;



	return pt_maillon;
}

// insere en tete le maillon, cf cours algo
void __insere_tete(t_objet3d *pt_objet, t_maillon *pt_maillon)
{
    pt_maillon->pt_suiv = pt_objet->tete;

	pt_objet->tete = pt_maillon; //On met en maillon suivant du maillon ajouté la tete actuelle, puis on remplace l'ancienne tete par cette nouvelle tête


}

t_objet3d *objet_vide()
{
	t_objet3d *pt_objet = NULL;
	pt_objet  = (t_objet3d*) malloc(sizeof(t_objet3d));
	pt_objet->est_camera = false;
	pt_objet->est_trie = false;
	pt_objet->tete = NULL;

	return pt_objet;
}

t_objet3d *camera()
{
	t_objet3d *pt_objet = NULL;
	pt_objet  = (t_objet3d*) malloc(sizeof(t_objet3d));
	pt_objet->est_camera = true;
	pt_objet->est_trie = false;
	pt_objet->tete = NULL;

	return pt_objet;
}

t_objet3d* parallelepipede(double lx, double ly, double lz)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();
	t_point3d *p0 = definirPoint3d(-lx,-ly,-lz);
	t_point3d *p1 = definirPoint3d(-lx,-ly,lz);
	t_point3d *p2 = definirPoint3d(-lx,ly,-lz);
	t_point3d *p3 = definirPoint3d(-lx,ly,lz);
	t_point3d *p4 = definirPoint3d(lx,-ly,-lz);
	t_point3d *p5 = definirPoint3d(lx,-ly,lz);
	t_point3d *p6 = definirPoint3d(lx,ly,-lz);
	t_point3d *p7 = definirPoint3d(lx,ly,lz);

	t_triangle3d *face11 = definirTriangle3d(p0, p1, p2);
	t_triangle3d *face12 = definirTriangle3d(p1, p2, p3);

	t_triangle3d *face21 = definirTriangle3d(p0, p2, p6);
	t_triangle3d *face22 = definirTriangle3d(p0, p4, p6);

	t_triangle3d *face31 = definirTriangle3d(p4, p5, p6);
	t_triangle3d *face32 = definirTriangle3d(p5, p6, p7);

	t_triangle3d *face41 = definirTriangle3d(p1, p5, p6);
	t_triangle3d *face42 = definirTriangle3d(p1, p3, p6);

	t_triangle3d *face51 = definirTriangle3d(p0, p1, p5);
	t_triangle3d *face52 = definirTriangle3d(p0, p4, p5);

	t_triangle3d *face61 = definirTriangle3d(p2, p3, p6);
	t_triangle3d *face62 = definirTriangle3d(p2, p3, p7);


	t_maillon *m11 = __cree_maillon(face11, ROUGEC);
	t_maillon *m21 = __cree_maillon(face21, ROUGEF);
	t_maillon *m31 = __cree_maillon(face31, NOIR);
	t_maillon *m41 = __cree_maillon(face41, BLEUC);
	t_maillon *m51 = __cree_maillon(face51, BLEUF);
	t_maillon *m61 = __cree_maillon(face61, VERTC);

	t_maillon *m12 = __cree_maillon(face12, VERTF);
	t_maillon *m22 = __cree_maillon(face22, NOIR);
	t_maillon *m32 = __cree_maillon(face32, JAUNEC);
	t_maillon *m42 = __cree_maillon(face42, JAUNEF);
	t_maillon *m52 = __cree_maillon(face52, 50);
	t_maillon *m62 = __cree_maillon(face62, 60);

	__insere_tete(pt_objet, m11);
	__insere_tete(pt_objet, m21);
	__insere_tete(pt_objet, m31);
	__insere_tete(pt_objet, m41);
	__insere_tete(pt_objet, m51);
	__insere_tete(pt_objet, m61);
	__insere_tete(pt_objet, m12);
	__insere_tete(pt_objet, m22);
	__insere_tete(pt_objet, m32);
	__insere_tete(pt_objet, m42);
	__insere_tete(pt_objet, m52);
	__insere_tete(pt_objet, m62);
	__trier_objet(pt_objet);




	return pt_objet;
}

t_objet3d* parallelepipede2(double lx, double ly, double lz, Uint32 couleur)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();
	t_point3d *p0 = definirPoint3d(-lx,-ly,-lz);
	t_point3d *p1 = definirPoint3d(-lx,-ly,lz);
	t_point3d *p2 = definirPoint3d(-lx,ly,-lz);
	t_point3d *p3 = definirPoint3d(-lx,ly,lz);
	t_point3d *p4 = definirPoint3d(lx,-ly,-lz);
	t_point3d *p5 = definirPoint3d(lx,-ly,lz);
	t_point3d *p6 = definirPoint3d(lx,ly,-lz);
	t_point3d *p7 = definirPoint3d(lx,ly,lz);

	t_triangle3d *face11 = definirTriangle3d(p0, p1, p2);
	t_triangle3d *face12 = definirTriangle3d(p1, p2, p3);

	t_triangle3d *face21 = definirTriangle3d(p0, p2, p6);
	t_triangle3d *face22 = definirTriangle3d(p0, p4, p6);

	t_triangle3d *face31 = definirTriangle3d(p4, p5, p6);
	t_triangle3d *face32 = definirTriangle3d(p5, p6, p7);

	t_triangle3d *face41 = definirTriangle3d(p1, p5, p6);
	t_triangle3d *face42 = definirTriangle3d(p1, p3, p6);

	t_triangle3d *face51 = definirTriangle3d(p0, p1, p5);
	t_triangle3d *face52 = definirTriangle3d(p0, p4, p5);

	t_triangle3d *face61 = definirTriangle3d(p2, p3, p6);
	t_triangle3d *face62 = definirTriangle3d(p2, p3, p7);


	t_maillon *m11 = __cree_maillon(face11, couleur);
	t_maillon *m21 = __cree_maillon(face21, couleur);
	t_maillon *m31 = __cree_maillon(face31, couleur);
	t_maillon *m41 = __cree_maillon(face41, couleur);
	t_maillon *m51 = __cree_maillon(face51, couleur);
	t_maillon *m61 = __cree_maillon(face61, couleur);

	t_maillon *m12 = __cree_maillon(face12, couleur);
	t_maillon *m22 = __cree_maillon(face22, couleur);
	t_maillon *m32 = __cree_maillon(face32, couleur);
	t_maillon *m42 = __cree_maillon(face42, couleur);
	t_maillon *m52 = __cree_maillon(face52, couleur);
	t_maillon *m62 = __cree_maillon(face62, couleur);

	__insere_tete(pt_objet, m11);
	__insere_tete(pt_objet, m21);
	__insere_tete(pt_objet, m31);
	__insere_tete(pt_objet, m41);
	__insere_tete(pt_objet, m51);
	__insere_tete(pt_objet, m61);
	__insere_tete(pt_objet, m12);
	__insere_tete(pt_objet, m22);
	__insere_tete(pt_objet, m32);
	__insere_tete(pt_objet, m42);
	__insere_tete(pt_objet, m52);
	__insere_tete(pt_objet, m62);
	__trier_objet(pt_objet);




	return pt_objet;
}

t_objet3d* sphere(double r, double nlat, double nlong)
{
	t_objet3d *pt_objet = NULL;
	int i,j,k;

	pt_objet = objet_vide();
	t_point3d *p[(int)nlat][(int)nlong];
	t_triangle3d *tbase1[(int)nlong], *tbase2[(int)nlong];

	for(i=0;i<nlat;i++) {
        for(j=0;j<nlong;j++) {
                p[i][j] = definirPoint3d(r*cos(1.57*((2*i)/nlat-1))*cos(3*14*((2*j)/nlong-1)),r*cos(1.57*((2*i)/nlat-1))*sin(3.14*((2*j)/nlong-1)),r*sin(1.57*((2*i)/nlat-1)));

        }
	}

	for(j=0;j<nlong;j++) {
        tbase1[j] = definirTriangle3d(p[0][0],p[1][j],p[1][j+1]);
        tbase2[j] = definirTriangle3d(p[(int)nlat][0],p[(int)nlat-1][j],p[(int)nlat-1][j+1]);
	}

	for(i=1;i<nlat-1;i++) {
        for(j=0;j<nlong-1;j++) {
                __insere_tete(pt_objet,__cree_maillon(definirTriangle3d(p[i][j],p[i+1][j],p[i][j+1]),10));
                __insere_tete(pt_objet,__cree_maillon(definirTriangle3d(p[i+1][j+1],p[i+1][j],p[i][j+1]),10));

        }
	}

	return pt_objet;
}

t_objet3d* sphere_amiga(double r, double nlat, double nlong)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();

	// TODO


	return pt_objet;
}

t_objet3d* arbre(double lx, double ly, double lz)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();
	// TODO

	return pt_objet;

}

t_objet3d* damier(double lx, double lz, double nx, double nz)
{
	t_objet3d *pt_objet = NULL;
	int i, j;
	t_objet3d *p;

	pt_objet = objet_vide();

	for(i=0;i<nx;i++) {
        for (j=0;j<nz;j++) {
                p = parallelepipede2(lx,0.1,lz,((i+j)%2)*100);
                translationObjet3d(p,definirVecteur3d(nx*i,0,nz*j));
                composerObjet3d(pt_objet,p);
        }
	}

	return pt_objet;

}

t_objet3d* cone(double lx, double lz, double nx, double nz, double r)
{
	t_objet3d *pt_objet = NULL;
	int i, j;
	double r1;
	t_point3d *p[(int)nx][(int)nz];

	pt_objet = objet_vide();

	for(i=0;i<nz;i++) {
            r1 = r*i/nz;
        for(j=0;j<nx;j++) {
             p[i][j]  = definirVecteur3d(r1*cos(3.14*j/nz),r1*sin(3.14*j/nz),-lz*i/nz);

        }
	}
    for(i=1;i<nz;i++) { //pour l'instant je ne traite pas le cas de base.
        for(j=0;j<nx;j++) {
            __insere_tete(pt_objet,__cree_maillon(definirTriangle3d(p[i][j],p[i+1][j],p[i][j+1]),10));
            __insere_tete(pt_objet,__cree_maillon(definirTriangle3d(p[i+1][j+1],p[i+1][j],p[i][j+1]),10));
        }
    }


	return pt_objet;

}

t_objet3d *copierObjet3d(t_objet3d *o) // attention, effectue une copie mirroir
{
	t_objet3d *n = objet_vide();

	n->est_camera=false;
	n->est_trie=o->est_trie;
    copierchaine(o->tete, n->tete);


	return n;
}

void copierchaine(t_maillon *m1, t_maillon *m2) //m1 est copié dans m2
{
    if (m1!=NULL) {
        t_maillon *m = __cree_maillon(m1->face, m1->couleur);
        m2 = m;
        copierchaine(m1->pt_suiv, m2->pt_suiv);
    }


}

void ajouterchaine(t_maillon *m1, t_maillon *m2) //m1 = m1m2
{
    if (m1!=NULL) {
        copierchaine(m1->pt_suiv, m2);
    } else if (m2!=NULL) {
    copierchaine(m2,m1);
    } //En gros, si on est au bout de la branche, on commence à y insérer les reste de m2


}

void composerObjet3d(t_objet3d* o, t_objet3d* o2) /* o = o+o2, o2 ne signifiera plus rien */
{

	ajouterchaine(o->tete,o2->tete);
	libererchaine(o2->tete);

}

void libererchaine(t_maillon *t)
{
    if (t!=NULL) {
        libererchaine(t->pt_suiv);
        free(t);
    }
}
void libererObjet3d(t_objet3d *o)
{

	libererchaine(o->tete);
	free(o);


}

double zface(t_maillon *m)
{
    if (m!=NULL) {
    t_triangle3d *lol = copierTriangle3d(m->face);
    t_point3d *p0 = lol->abc[0];
    t_point3d *p1 = lol->abc[1];
    t_point3d *p2 = lol->abc[2];

    return (double) (p0->xyzt[2]+p1->xyzt[2]+p2->xyzt[2])*0.33 ;
    } else {return 0;}

}

void trierchaine(t_maillon *m)
{
    if (m->pt_suiv!=NULL)
    {
        trierchaine(m->pt_suiv);
        if (zface(m) > zface(m->pt_suiv))
        {
            t_maillon *k1 = __copier_maillon(m);
            t_maillon *k2 = __copier_maillon(m->pt_suiv);

            m->face = k2->face;
            m->couleur = k2 -> couleur;

            k2->face = k1->face;
            k2->couleur = k1 -> couleur;

            m->pt_suiv = __copier_maillon(k2);
        }
    }
}

//effectue un tri des faces de l'objet dans l'ordre des z decroissants => cf algorithme du peintre
void __trier_objet(t_objet3d *pt_objet)
{
    trierchaine(pt_objet->tete);
}

void dessinerObjet3d(t_surface *surface, t_objet3d* pt_objet)
{
    t_maillon *lol = __copier_maillon(pt_objet->tete);
	while(lol->pt_suiv!=NULL) {
        remplirTriangle3d(surface, lol->face, lol->couleur);
        lol = __copier_maillon(lol->pt_suiv);
	}

}

void translationObjet3d(t_objet3d* pt_objet, t_point3d *vecteur)
{
	t_maillon *lol = __copier_maillon(pt_objet->tete);
	while(lol->pt_suiv!=NULL) {
        translationTriangle3d(lol->face, vecteur);
        lol = __copier_maillon(lol->pt_suiv);
	}
	free(lol);

	//__trier_objet(pt_objet);

}

void rotationObjet3d(t_objet3d* pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ)
{
	t_maillon *lol = __copier_maillon(pt_objet->tete);
	//while(lol!=NULL) {
   //     rotationTriangle3d(lol->face, centre, degreX, degreY, degreZ);
    //    lol = __copier_maillon(lol->pt_suiv);
	//}

	//__trier_objet(pt_objet);


}

void transformationObjet3d(t_objet3d* pt_objet, double mat[4][4])
{
	// TODO

}

