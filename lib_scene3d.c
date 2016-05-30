#include <assert.h>
#include <math.h>
#include "lib_3d.h"
#include "lib_objet3d.h"
#include "lib_mat.h"
#include "lib_surface.h"
#include "lib_scene3d.h"

#define MATRICE_IDENTITE (double[4][4]){{1., 0., 0., 0.},{0., 1., 0., 0.},{0., 0., 1., 0.},{0., 0., 0., 1.}}

t_scene3d* definirScene3d(t_objet3d *pt_objet)
{
	t_scene3d* pt_maillon;
	double m1[4][4] = {{1, 0, 0, 0},\
			{0, 1, 0, 0},\
			{0, 0, 1, 0},\
			{0, 0, 0, 1}};

	pt_maillon->objet = pt_objet;
	copierMatrice3d(pt_maillon->descendant,m1);
	copierMatrice3d(pt_maillon->montant,m1);


	return pt_maillon;
}

t_scene3d* ajouter_relation(t_scene3d* pt_feuille, t_objet3d *pt_objet) // ajout de l'objet en tete des fils
{
	t_scene3d* pt_maillon = definirScene3d(pt_objet);

	if (pt_maillon!=NULL)
	{
		pt_maillon->pt_pere = pt_feuille;
		pt_maillon->pt_suiv = pt_feuille->pt_fils;
		pt_feuille->pt_fils = pt_maillon;
	}

	return pt_maillon; // on retourne le lien vers la nouvelle sous scene
}

void translationScene3d(t_scene3d *pt_scene, t_point3d *vecteur)
{
    double m1[4][4] ={{1, 0, 0, (vecteur->xyzt[0])},\
			{0, 1, 0, (vecteur->xyzt[1])},\
			{0, 0, 1, (vecteur->xyzt[2])},\
			{0, 0, 0, 1}};
    double m2[4][4] ={{1, 0, 0, -(vecteur->xyzt[0])},\
			{0, 1, 0, -(vecteur->xyzt[1])},\
			{0, 0, 1, -(vecteur->xyzt[2])},\
			{0, 0, 0, 1}};
    double m3[4][4], m4[4][4];
    copierMatrice3d(m3,pt_scene->montant);
    copierMatrice3d(m4,pt_scene->descendant);

    multiplicationMatrice3d(pt_scene->montant,m3,m2);
    multiplicationMatrice3d(pt_scene->descendant,m1,m4);




}


void rotationScene3d(t_scene3d *pt_scene, t_point3d *centre, float degreX, float degreY, float degreZ)
{

  // TODO
}

void dessinerSceneR(t_scene3d* rektos, double mat[4][4], t_objet3d *aremplir)
{
    if(rektos!=NULL) {
        double mat2[4][4];
        t_objet3d *ajouter = copierObjet3d(rektos->objet);

        multiplicationMatrice3d(mat2, rektos->descendant, mat);
        transformationObjet3d(ajouter,mat2);
        composerObjet3d(aremplir, ajouter);


        libererObjet3d(ajouter);


        dessinerSceneR(rektos->pt_fils,mat2,aremplir);
        dessinerSceneR(rektos->pt_suiv,mat,aremplir);
    }
}


void dessinerScene3d(t_surface *surface, t_scene3d* pt_racine)
{
    double mat1[4][4] = {{1, 0, 0, 0},\
			{0, 1, 0, 0},\
			{0, 0, 1, 0},\
			{0, 0, 0, 1}};

    t_objet3d *place = objet_vide();
    dessinerSceneR(pt_racine->pt_fils, mat1, place);

    __trier_objet(place);
    dessinerObjet3d(surface, place);

    libererObjet3d(place);

}

/*
 * // il faut multiplier mes matrices \E0 celles du p\E8re pour inverser la relation
  copier_matrice(m, pt_pere->descendant);
  multiplication_matrice(pt_pere->descendant, pt_objet->montant, m);
  copier_matrice(m, pt_pere->montant);
  multiplication_matrice(pt_pere->montant, pt_objet->descendant, m);
*/

void changerCamera(t_scene3d *pt_objet) // modifie l'arbre de la scene pour que pt_objet en soit la racine, pt_racine ne veut plus rien dire
{

  //TODO
}
