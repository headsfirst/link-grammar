/*************************************************************************/
/* Copyright (c) 2009 Linas Vepstas                                      */
/* All rights reserved                                                   */
/*                                                                       */
/* Use of the link grammar parsing system is subject to the terms of the */
/* license set forth in the LICENSE file included with this software,    */
/* and also available at http://www.link.cs.cmu.edu/link/license.html    */
/* This license allows free redistribution and use in source and binary  */
/* forms, with or without modification, subject to certain conditions.   */
/*                                                                       */
/*************************************************************************/
/*
 * expand.c
 *
 * Enlarge the range of possible disjunct to consider while parsing.
 */

#include "api-structures.h"
#include "expand.h"
#include "disjunct-utils.h"
#include "word-utils.h"
#include "corpus/cluster.h"

/* ========================================================= */

static Disjunct * build_expansion_disjuncts(Cluster *clu, X_node *x)
{
	Disjunct *dj;
	printf("Expanding ... %s \n", x->string);
	dj = lg_cluster_get_disjuncts(clu, x->string);
	return dj;
}

/**
 */
void lg_expand_disjunct_list(Sentence sent)
{
	int w;

	Cluster *clu = lg_cluster_new();

	for (w = 0; w < sent->length; w++)
	{
		X_node * x;
		Disjunct * d = sent->word[w].d;
		for (x = sent->word[w].x; x != NULL; x = x->next)
		{
			Disjunct *dx = build_expansion_disjuncts(clu, x);
			d = catenate_disjuncts(dx, d);
		}
		sent->word[w].d = d;
	}
	lg_cluster_delete(clu);
}

