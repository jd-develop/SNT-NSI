-- question 2
SELECT
	name
FROM
	villagers
WHERE
	color = "Red";

-- question 3
SELECT DISTINCT
	color
FROM
	villagers;
	
-- question 4
SELECT
	*
FROM
	villagers
WHERE
	birthday = "06-13";
	
-- question 5
SELECT
	*
FROM
	wallpapers
ORDER BY
	price DESC
LIMIT 7
OFFSET 4;

-- question 6
SELECT
	id, name, price, type
FROM
	articles
GROUP BY
	id
ORDER BY
	price DESC
LIMIT 10;

-- question 7
SELECT DISTINCT
	date
FROM
	purchases
WHERE
	amount = 7;

-- question 8
SELECT
	birthday
FROM
	villagers v
WHERE
	v.style = "Cool"
EXCEPT SELECT
	date
FROM
	purchases p
WHERE
	p.amount = 7;

-- question 9
/* Cette requête donne le nom, la couleur et la couleur du papier peint de tous les villageois qui ont une couleur différente de celle de leur papier peint */

-- question 10
SELECT
	parrain.name
FROM
	villagers parrain
JOIN
	referral
ON
	parrain.id = referral.id_referrer
JOIN
	villagers filleul
ON
	filleul.id = referral.id_referee
WHERE
	filleul.name = "Charlise";
	
-- question 11
SELECT
	name
FROM
	referral
JOIN
	villagers
ON
	villagers.id = referral.id_referee
WHERE
	referral.id_referee = referral.id_referrer;

-- question 12
SELECT 
	count(*)
FROM
	villagers v
JOIN
	purchases p
ON
	p.villager_id = v.id AND p.date = v.birthday;

-- question 13
SELECT DISTINCT
	v.name
FROM
	villagers v
JOIN
	purchases p
ON
	p.villager_id = v.id
JOIN
	articles a
ON
	p.article_id = a.id AND p.variant_id = a.variant_id
WHERE
	a.color <> v.color;
	
-- question 14
SELECT
	v.name
FROM
	villagers v
JOIN
	purchases
ON
	villager_id = id
EXCEPT SELECT
	v2.name
FROM
	villagers v2
JOIN
	purchases p
ON
	p.villager_id = v2.id
JOIN
	articles a
ON
	p.article_id = a.id AND p.variant_id = a.variant_id
WHERE
	a.color = v2.color;

-- question 15
/* Cette reqête compte le nombre de villageois de chaque couleur */

-- question 16
SELECT
	v.name, SUM(p.amount) AS nb_article_achetes, MAX(a.price) AS prix_article_le_plus_cher, MIN(a.price) AS prix_article_le_moins_cher
FROM
	villagers v
JOIN
	purchases p
ON
	v.id = p.villager_id
JOIN
	articles a
ON
	a.id = p.article_id AND a.variant_id = p.variant_id
GROUP BY
	v.name;
	
-- question 17
SELECT
	species, color, style, count(*) as tot
FROM
	villagers v
GROUP BY
	species, color, style
ORDER BY
	tot DESC
LIMIT 10;

-- question 18
SELECT
	v.name, AVG(a.price) as moyenne_prix
FROM
	villagers v
JOIN
	purchases p
ON
	v.id = p.villager_id
JOIN
	articles a
ON
	a.id = p.article_id AND a.variant_id = p.variant_id
GROUP BY
	v.name
ORDER BY
	moyenne_prix ASC
LIMIT 10;

-- question 19
SELECT
	v.name, SUM(a.price*p.amount) AS total_depense
FROM
	villagers v
JOIN
	purchases p
ON
	v.id = p.villager_id AND p.date <= "03-31"
JOIN
	articles a
ON
	a.id = p.article_id AND a.variant_id = p.variant_id
GROUP BY
	v.name
ORDER BY
	total_depense DESC
LIMIT 5;

-- question 20
SELECT
	v.name, SUM(a.price*p.amount) AS total_depense
FROM
	villagers v
JOIN
	purchases p
ON
	v.id = p.villager_id AND p.date <= "03-31"
JOIN
	articles a
ON
	a.id = p.article_id AND a.variant_id = p.variant_id
GROUP BY
	v.name
HAVING
	40000 <= total_depense AND total_depense <= 50000
ORDER BY
	total_depense DESC;
	
-- question 21
/*
def requete(n: int):
    print("SELECT")
    print("    filleuls.name as filleul,")
    for i in range(1, n+1):
        print(f"    v{i}.name as parrain{i}", end=(",\n" if i!=n else "\n"))
    print("FROM referral r1")
    for i in range(2, n+1):
        print(f"JOIN referral r{i} ON r{i}.id_referee = r{i-1}.id_referrer AND r{i}.id_referee <> r{i}.id_referrer")
    print("JOIN villagers filleuls ON r1.id_referee = filleuls.id")
    for i in range(1, n+1):
        print(f"JOIN villagers v{i} ON r{i}.id_referrer = v{i}.id")
    print("WHERE")
    for i in range(2, n+1):
        print(f"    r{i}.id_referee <> r1.id_referee", end=(" AND\n" if i!=n else ";\n"))


requete(22)
*/
SELECT
    filleuls.name as filleul,
    v1.name as parrain1,
    v2.name as parrain2,
    v3.name as parrain3,
    v4.name as parrain4,
    v5.name as parrain5,
    v6.name as parrain6,
    v7.name as parrain7,
    v8.name as parrain8,
    v9.name as parrain9,
    v10.name as parrain10,
    v11.name as parrain11,
    v12.name as parrain12,
    v13.name as parrain13,
    v14.name as parrain14,
    v15.name as parrain15,
    v16.name as parrain16,
    v17.name as parrain17,
    v18.name as parrain18,
    v19.name as parrain19,
    v20.name as parrain20,
    v21.name as parrain21,
    v22.name as parrain22
FROM referral r1
JOIN referral r2 ON r2.id_referee = r1.id_referrer AND r2.id_referee <> r2.id_referrer
JOIN referral r3 ON r3.id_referee = r2.id_referrer AND r3.id_referee <> r3.id_referrer
JOIN referral r4 ON r4.id_referee = r3.id_referrer AND r4.id_referee <> r4.id_referrer
JOIN referral r5 ON r5.id_referee = r4.id_referrer AND r5.id_referee <> r5.id_referrer
JOIN referral r6 ON r6.id_referee = r5.id_referrer AND r6.id_referee <> r6.id_referrer
JOIN referral r7 ON r7.id_referee = r6.id_referrer AND r7.id_referee <> r7.id_referrer
JOIN referral r8 ON r8.id_referee = r7.id_referrer AND r8.id_referee <> r8.id_referrer
JOIN referral r9 ON r9.id_referee = r8.id_referrer AND r9.id_referee <> r9.id_referrer
JOIN referral r10 ON r10.id_referee = r9.id_referrer AND r10.id_referee <> r10.id_referrer
JOIN referral r11 ON r11.id_referee = r10.id_referrer AND r11.id_referee <> r11.id_referrer
JOIN referral r12 ON r12.id_referee = r11.id_referrer AND r12.id_referee <> r12.id_referrer
JOIN referral r13 ON r13.id_referee = r12.id_referrer AND r13.id_referee <> r13.id_referrer
JOIN referral r14 ON r14.id_referee = r13.id_referrer AND r14.id_referee <> r14.id_referrer
JOIN referral r15 ON r15.id_referee = r14.id_referrer AND r15.id_referee <> r15.id_referrer
JOIN referral r16 ON r16.id_referee = r15.id_referrer AND r16.id_referee <> r16.id_referrer
JOIN referral r17 ON r17.id_referee = r16.id_referrer AND r17.id_referee <> r17.id_referrer
JOIN referral r18 ON r18.id_referee = r17.id_referrer AND r18.id_referee <> r18.id_referrer
JOIN referral r19 ON r19.id_referee = r18.id_referrer AND r19.id_referee <> r19.id_referrer
JOIN referral r20 ON r20.id_referee = r19.id_referrer AND r20.id_referee <> r20.id_referrer
JOIN referral r21 ON r21.id_referee = r20.id_referrer AND r21.id_referee <> r21.id_referrer
JOIN referral r22 ON r22.id_referee = r21.id_referrer AND r22.id_referee <> r22.id_referrer
JOIN villagers filleuls ON r1.id_referee = filleuls.id
JOIN villagers v1 ON r1.id_referrer = v1.id
JOIN villagers v2 ON r2.id_referrer = v2.id
JOIN villagers v3 ON r3.id_referrer = v3.id
JOIN villagers v4 ON r4.id_referrer = v4.id
JOIN villagers v5 ON r5.id_referrer = v5.id
JOIN villagers v6 ON r6.id_referrer = v6.id
JOIN villagers v7 ON r7.id_referrer = v7.id
JOIN villagers v8 ON r8.id_referrer = v8.id
JOIN villagers v9 ON r9.id_referrer = v9.id
JOIN villagers v10 ON r10.id_referrer = v10.id
JOIN villagers v11 ON r11.id_referrer = v11.id
JOIN villagers v12 ON r12.id_referrer = v12.id
JOIN villagers v13 ON r13.id_referrer = v13.id
JOIN villagers v14 ON r14.id_referrer = v14.id
JOIN villagers v15 ON r15.id_referrer = v15.id
JOIN villagers v16 ON r16.id_referrer = v16.id
JOIN villagers v17 ON r17.id_referrer = v17.id
JOIN villagers v18 ON r18.id_referrer = v18.id
JOIN villagers v19 ON r19.id_referrer = v19.id
JOIN villagers v20 ON r20.id_referrer = v20.id
JOIN villagers v21 ON r21.id_referrer = v21.id
JOIN villagers v22 ON r22.id_referrer = v22.id
WHERE
    r2.id_referee <> r1.id_referee AND
    r3.id_referee <> r1.id_referee AND
    r4.id_referee <> r1.id_referee AND
    r5.id_referee <> r1.id_referee AND
    r6.id_referee <> r1.id_referee AND
    r7.id_referee <> r1.id_referee AND
    r8.id_referee <> r1.id_referee AND
    r9.id_referee <> r1.id_referee AND
    r10.id_referee <> r1.id_referee AND
    r11.id_referee <> r1.id_referee AND
    r12.id_referee <> r1.id_referee AND
    r13.id_referee <> r1.id_referee AND
    r14.id_referee <> r1.id_referee AND
    r15.id_referee <> r1.id_referee AND
    r16.id_referee <> r1.id_referee AND
    r17.id_referee <> r1.id_referee AND
    r18.id_referee <> r1.id_referee AND
    r19.id_referee <> r1.id_referee AND
    r20.id_referee <> r1.id_referee AND
    r21.id_referee <> r1.id_referee AND
    r22.id_referee <> r1.id_referee;
