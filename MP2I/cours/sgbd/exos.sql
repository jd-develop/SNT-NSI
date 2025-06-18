-- exercice 1, question 1

SELECT
	v.nom
FROM
	agglomeration AS v
JOIN
	habite AS h
	ON v.code = h.code_agglo
JOIN
	personne AS p
	ON p.id_pers = h.id_pers
WHERE
	p.prenom = "Claire"
	AND p.nom = "Igname"
ORDER BY
	h.debut ASC
LIMIT 1;

-- Exercice 1, question 2

SELECT
	p1.prenom, p1.nom, p2.prenom, p2.nom, a.nom -- , h1.debut, h1.fin, h2.debut, h2.fin
FROM
	personne AS p1
JOIN
	habite AS h1
	ON h1.id_pers = p1.id_pers
JOIN
	habite AS h2
	ON h1.code_agglo = h2.code_agglo
JOIN
	personne AS p2
	ON h2.id_pers = p2.id_pers
JOIN
	agglomeration AS a
	ON h1.code_agglo = a.code
WHERE 
	h1.debut <= h2.fin
	AND h2.debut <= h1.fin
	AND h1.idhabite < h2.idhabite;