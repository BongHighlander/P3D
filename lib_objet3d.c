#include <assert.h>
#include <math.h>
#include "lib_3d.h"
#include "lib_objet3d.h"
#include "lib_mat.h"
#include "lib_surface.h"


// cree un nouveau maillon, cf cours algo
t_maillon* __cree_maillon(t_triangle3d *face, Uint32 couleur)
{
	t_maillon* p = NULL;
	p  = (t_maillon*) malloc(sizeof(t_maillon)); //malloc de circonstance, encore
	if (p!=NULL)
	{
		p->face = face;
		p->couleur = couleur;
		p->pt_suiv = NULL; //pour l'instant, pas de suivant
	}

	return p;
}

// insere en tete le maillon, cf cours algo
void __insere_tete(t_objet3d *pt_objet, t_maillon *pt_maillon)
{
	pt_maillon->pt_suiv = pt_objet->tete; //ici, objet->tete et maillon->tete

	pt_objet->tete = pt_maillon; //ici, objet->maillon->(ancienne) tete


}

t_objet3d *objet_vide()
{
	t_objet3d *pt_objet = NULL;
	pt_objet = (t_objet3d*) malloc(sizeof(t_objet3d));

	if(pt_objet!=NULL)
    {
        pt_objet->est_camera = false;
        pt_objet->est_trie = true;
        pt_objet->tete = NULL;
    }


	return pt_objet;
}

t_objet3d *camera()
{
	return objet_vide();
}

t_objet3d* parallelepipede(double lx, double ly, double lz, Uint32 couleur)
{

	t_point3d *p0,*p1,*p2,*p3,*p4,*p5,*p6,*p7;
	t_objet3d *o1 = NULL;

	p0 = definirPoint3d(-lx,-ly,-lz);
	p1 = definirPoint3d(-lx,-ly,lz);
	p2 = definirPoint3d(-lx,ly,-lz);
	p3 = definirPoint3d(-lx,ly,lz);
	p4 = definirPoint3d(lx,-ly,-lz);
	p5 = definirPoint3d(lx,-ly,lz);
	p6 = definirPoint3d(lx,ly,-lz);
	p7 = definirPoint3d(lx,ly,lz);

	o1 = objet_vide();

	__insere_tete(o1,__cree_maillon(copierTriangle3d(definirTriangle3d(p0,p1,p2)),couleur));
	__insere_tete(o1,__cree_maillon(copierTriangle3d(definirTriangle3d(p1,p2,p3)),couleur));

	__insere_tete(o1,__cree_maillon(copierTriangle3d(definirTriangle3d(p4,p5,p6)),couleur));
	__insere_tete(o1,__cree_maillon(copierTriangle3d(definirTriangle3d(p5,p6,p7)),couleur));

	__insere_tete(o1,__cree_maillon(copierTriangle3d(definirTriangle3d(p2,p3,p6)),couleur));
	__insere_tete(o1,__cree_maillon(copierTriangle3d(definirTriangle3d(p3,p6,p7)),couleur));

	__insere_tete(o1,__cree_maillon(copierTriangle3d(definirTriangle3d(p0,p1,p4)),couleur));
	__insere_tete(o1,__cree_maillon(copierTriangle3d(definirTriangle3d(p1,p4,p5)),couleur));

	__insere_tete(o1,__cree_maillon(copierTriangle3d(definirTriangle3d(p0,p2,p4)),couleur));
	__insere_tete(o1,__cree_maillon(copierTriangle3d(definirTriangle3d(p2,p4,p6)),couleur));

	__insere_tete(o1,__cree_maillon(copierTriangle3d(definirTriangle3d(p1,p3,p5)),couleur));
	__insere_tete(o1,__cree_maillon(copierTriangle3d(definirTriangle3d(p3,p5,p7)),couleur));

	free(p0);
	free(p1);
	free(p2);
	free(p3);
	free(p4);
	free(p5);
	free(p6);
	free(p7);

	return o1;
}

t_objet3d* sphere(double r, double nlat, double nlong)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();
	t_point3d *corps[(int)(nlat-1)][(int)(nlong)];
	t_point3d *sommet, *antisommet;
	int i,j;
	sommet = definirPoint3d(0,0,r);
	antisommet = definirPoint3d(0,0,-r);
	Uint32 couleura = JAUNEC;
	//cos(1.57*(2*(i+1)/nlat))
	//cos(3.14*(2*j/nlong))

	for(i=0;i<nlat-1;i++) {
        for(j=0;j<nlong;j++) {
            corps[i][j] = definirPoint3d(r*cos(1.57*(2*(i+1)/nlat-1))*cos(3.14*(2*j/nlong-1)),r*cos(1.57*(2*(i+1)/nlat-1))*sin(3.14*(2*j/nlong-1)),r*sin(1.57*(2*(i+1)/nlat-1)));
        }
	}

	for(i=1;i<nlat-1;i++) {
        for(j=1;j<nlong;j++) {
            __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(corps[i-1][j-1],corps[i-1][j],corps[i][j-1])),couleura));
            __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(corps[i][j],corps[i][j-1],corps[i-1][j])),couleura));
        }
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(corps[i-1][(int)(nlong-1)],corps[i-1][0],corps[i][(int)(nlong-1)])),couleura));
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(corps[i][0],corps[i][(int)(nlong-1)],corps[i-1][0])),couleura));
	}
	for(j=1;j<nlong;j++) {
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(antisommet,corps[0][j],corps[0][j-1])),couleura));
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(sommet,corps[(int)(nlat-2)][j],corps[(int)(nlat-2)][j-1])),couleura));
	}
	__insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(sommet,corps[(int)(nlat-2)][0],corps[(int)(nlat-2)][(int)(nlong-1)])),couleura));
	__insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(antisommet,corps[0][0],corps[0][(int)(nlong-1)])),couleura));



            //ROUGEC*(j%2)+BLANC*((j+1)%2)astuce de code pour alterner les couleurs

	for(i=0;i<nlat-2;i++) {
        for(j=0;j<nlong;j++) {
            free(corps[i][j]);
        }
	}
	free(sommet);
	free(antisommet);




	return pt_objet;
}

t_objet3d* sphere_amiga(double r, double nlat, double nlong)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();
	t_point3d *corps[(int)(nlat-1)][(int)(nlong)];
	t_point3d *sommet, *antisommet;
	int i,j;
	sommet = definirPoint3d(0,0,r);
	antisommet = definirPoint3d(0,0,-r);
	//cos(1.57*(2*(i+1)/nlat))
	//cos(3.14*(2*j/nlong))

	for(i=0;i<nlat-1;i++) {
        for(j=0;j<nlong;j++) {
            corps[i][j] = definirPoint3d(r*cos(1.57*(2*(i+1)/nlat-1))*cos(3.14*(2*j/nlong-1)),r*cos(1.57*(2*(i+1)/nlat-1))*sin(3.14*(2*j/nlong-1)),r*sin(1.57*(2*(i+1)/nlat-1)));
        }
	}

	for(i=1;i<nlat-1;i++) {
        for(j=1;j<nlong;j++) {
            __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(corps[i-1][j-1],corps[i-1][j],corps[i][j-1])),ROUGEC*((j+i)%2)+BLANC*((i+j+1)%2)));
            __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(corps[i][j],corps[i][j-1],corps[i-1][j])),ROUGEC*((i+j)%2)+BLANC*((i+j+1)%2)));
        }
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(corps[i-1][(int)(nlong-1)],corps[i][0],corps[i][(int)(nlong-1)])),ROUGEC*((i+j)%2)+BLANC*((i+j+1)%2)));
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(corps[i][0],corps[i-1][(int)(nlong-1)],corps[i-1][0])),BLANC*((i+(int)(nlat-2))%2)+ROUGEC*((i+(int)(nlat-2)+1)%2)));
	}
	for(j=1;j<nlong;j++) {
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(antisommet,corps[0][j],corps[0][j-1])),ROUGEC*(j%2)+BLANC*((j+1)%2)));
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(sommet,corps[(int)(nlat-2)][j],corps[(int)(nlat-2)][j-1])),BLANC*(j%2)+ROUGEC*((j+1)%2)));
	}
	__insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(sommet,corps[(int)(nlat-2)][0],corps[(int)(nlat-2)][(int)(nlong-1)])),ROUGEC*((int)(nlong-1)%2)+BLANC*(((int)(nlong-1)+1)%2)));
	__insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(antisommet,corps[0][0],corps[0][(int)(nlong-1)])),BLANC*((int)(nlong-1)%2)+ROUGEC*(((int)(nlong-1)+1)%2)));



            //ROUGEC*(j%2)+BLANC*((j+1)%2)astuce de code pour alterner les couleurs

	for(i=0;i<nlat-2;i++) {
        for(j=0;j<nlong;j++) {
            free(corps[i][j]);
        }
	}
	free(sommet);
	free(antisommet);




	return pt_objet;
}

t_objet3d* cone(double hauteur,double largeur, double longi)
{
    t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();
	int i;

	t_point3d *cercle[(int)longi];
	t_point3d *sommet = definirPoint3d(0,-hauteur,0);
	t_point3d *centre = definirPoint3d(0,0,0);

	for(i=0;i<longi;i++) {
        cercle[i] = definirPoint3d(largeur*cos(6.28*i/longi),0,largeur*sin(6.28*i/longi));
	}

	for(i=1;i<longi;i++) {
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(sommet,cercle[i],cercle[i-1])),VERTC));
	}
	__insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(sommet,cercle[(int)(longi-1)],cercle[0])),VERTC)); //(int)(longi-1)

	for(i=1;i<longi;i++) {
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(centre,cercle[i],cercle[i-1])),VERTF));
	}
	__insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(centre,cercle[(int)(longi-1)],cercle[0])),VERTF)); //(int)(longi-1)

	for(i=0;i<longi;i++) {
        free(cercle[i]);
	}
	free(centre);


	return pt_objet;



}

t_objet3d* cylindre(double hauteur,double largeur, double longi)
{
    t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();
	int i;

	t_point3d *cercle1[(int)longi];
	t_point3d *cercle2[(int)longi];
	t_point3d *centre1 = definirPoint3d(0,-hauteur,0);
	t_point3d *centre2 = definirPoint3d(0,hauteur,0);

	for(i=0;i<longi;i++) {
        cercle1[i] = definirPoint3d(largeur*cos(6.28*i/longi),-hauteur,largeur*sin(6.28*i/longi));
        cercle2[i] = definirPoint3d(largeur*cos(6.28*i/longi),hauteur,largeur*sin(6.28*i/longi));
	}

	for(i=1;i<longi;i++) {
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(cercle1[i-1],cercle1[i],cercle2[i])),MARRON1));
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(cercle2[i-1],cercle2[i],cercle1[i-1])),MARRON1));
	}
	__insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(cercle2[(int)(longi-1)],cercle1[(int)(longi-1)],cercle1[0])),MARRON1));
	__insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(cercle1[0],cercle2[(int)(longi-1)],cercle2[0])),MARRON1)); //(int)(longi-1)

	for(i=1;i<longi;i++) {
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(centre1,cercle1[i],cercle1[i-1])),MARRON2));
        __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(centre2,cercle2[i],cercle2[i-1])),MARRON2));
	}
	__insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(centre1,cercle1[(int)(longi-1)],cercle1[0])),MARRON2));
	__insere_tete(pt_objet,__cree_maillon(copierTriangle3d(definirTriangle3d(centre2,cercle2[(int)(longi-1)],cercle2[0])),MARRON2)); //(int)(longi-1)

	for(i=0;i<longi;i++) {
        free(cercle1[i]);
        free(cercle2[i]);
	}
	free(centre1);
	free(centre2);


	return pt_objet;



}




t_objet3d* arbre(double lx, double ly, double lz)
{
	t_objet3d *pt_objet = NULL;
	t_objet3d *pt_marron = NULL;

	pt_objet = objet_vide();
	pt_marron = cylindre(lx,ly,10);
	translationObjet3d(pt_marron,definirPoint3d(0,lx,0));
	pt_objet = cone(lx,lz,10);
	composerObjet3d(pt_objet,pt_marron);

	libererObjet3d(pt_marron);

	return pt_objet;

}

t_objet3d* damier(double lx, double lz, double nx, double nz)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();
	int i,j;
	t_point3d *p0, *p1, *p2, *p3;
	p0 = definirPoint3d(0,0,0);
	p1 = definirPoint3d(lx,0,0);
	p2 = definirPoint3d(0,0,lz);
	p3 = definirPoint3d(lx,0,lz);

	t_triangle3d *damier1 = definirTriangle3d(p0,p1,p2);
	t_triangle3d *damier2 = definirTriangle3d(p3,p1,p2);

	for(i=0;i<nx;i++) {
            translationObjet3d(pt_objet,definirPoint3d(-lx*nx,0,0));
        for(j=0;j<nz;j++) {
                //translationTriangle3d(copierTriangle3d(damier1),p4)
                //BLANC*((i+j)%2)+NOIR*((i+j+1)%2)
                __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(damier1),BLANC*((i+j)%2)+NOIR*((i+j+1)%2)));
                __insere_tete(pt_objet,__cree_maillon(copierTriangle3d(damier2),BLANC*((i+j)%2)+NOIR*((i+j+1)%2)));
                translationObjet3d(pt_objet,p1);
        }
        translationObjet3d(pt_objet,p2);
	}
	translationObjet3d(pt_objet,definirPoint3d(-lx*nx*0.5,0,-lz*nz*0.5));

	libererTriangle3d(damier1);
	libererTriangle3d(damier2);


	return pt_objet;

}

t_objet3d *copierObjet3d(t_objet3d *o) // attention, effectue une copie mirroir
{
	t_objet3d *n = objet_vide();

	t_maillon *o1 = o->tete;
	while(o1!=NULL) {
            __insere_tete(n,__cree_maillon(o1->face,o1->couleur));
            o1 = o1->pt_suiv;
	}



	return n;
}

void composerObjet3d(t_objet3d* o, t_objet3d* o2) /* o = o+o2, o2 ne signifiera plus rien */
{
	t_maillon *o1 = o2->tete;
	while(o1!=NULL) {
            __insere_tete(o,__cree_maillon(copierTriangle3d(o1->face),o1->couleur));
            o1 = o1->pt_suiv;
	}


}

void libererObjet3d(t_objet3d *o)
{
	t_maillon *o1 = o->tete;
	t_maillon *o2;
	while(o1!=NULL) {
        o2 = o1;
        o1 = o1->pt_suiv;
        libererTriangle3d(o2->face);
        free(o2);
	}
	free(o);

}

void __insertion_tri(t_maillon *m1,t_objet3d *o1) //le maillon m1 est mis de manière triée dans o1 selon la règle des z
{
    t_maillon *m2 = o1->tete;
    if(moyenneZTriangle3d(m2->face)<moyenneZTriangle3d(m1->face)){
            __insere_tete(o1,m1);
    } else {
    while((moyenneZTriangle3d(m2->pt_suiv->face)>moyenneZTriangle3d(m1->face)) && (m2->pt_suiv!=NULL)) {
        m2 = m2->pt_suiv;
    }
    m1->pt_suiv = m2->pt_suiv;
    m2->pt_suiv = m1;
    }
}

//effectue un tri des faces de l'objet dans l'ordre des z decroissants => cf algorithme du peintre
void __trier_objet(t_objet3d *pt_objet)
{
	t_maillon *o1 = pt_objet->tete; //o1 pointe sur le maillon de tete
	t_maillon *o2;

	while(o1->pt_suiv!=NULL) {
            if(moyenneZTriangle3d(o1->face)<moyenneZTriangle3d(o1->pt_suiv->face)){
                o2 = o1->pt_suiv;
                o1->pt_suiv = o2->pt_suiv;
                __insertion_tri(o2,pt_objet);
            } else {o1 = o1->pt_suiv;} //si rien ne se passe, on passe au maillon suivant
	}
}

void dessinerObjet3d(t_surface *surface, t_objet3d* pt_objet)
{
	t_maillon *o1 = pt_objet->tete;
	while(o1!=NULL) {
        remplirTriangle3d(surface,o1->face,o1->couleur);
        o1 = o1->pt_suiv;
	}

}

void translationObjet3d(t_objet3d* pt_objet, t_point3d *vecteur)
{
	t_maillon *o1 = pt_objet->tete;
	while(o1!=NULL) {
        translationTriangle3d(o1->face,vecteur);
        o1 = o1->pt_suiv;
	}

}

void rotationObjet3d(t_objet3d* pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ)
{
    __trier_objet(pt_objet);
	t_maillon *o1 = pt_objet->tete;
	while(o1!=NULL) {
        rotationTriangle3d(o1->face,centre,degreX,degreY,degreZ);
        o1 = o1->pt_suiv;
	}

}

void transformationObjet3d(t_objet3d* pt_objet, double mat[4][4])
{

	t_maillon *o1 = pt_objet->tete;
	while(o1!=NULL) {
        transformationTriangle3d(o1->face,mat);
        o1 = o1->pt_suiv;
	}
	__trier_objet(pt_objet);

}

