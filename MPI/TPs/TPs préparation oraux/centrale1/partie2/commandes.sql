select distinct prenom
from prenoms
where length(prenom) = 1;

select prenom
from prenoms
group by prenom
having count(prenom)=1000;

select prenom
from prenoms
group by prenom
having sum(nombre)=1000;

select prenom, sum(nombre)
from prenoms
where sexe=2 and annee>=2001
group by prenom
order by sum(nombre) desc
limit 1 offset 4;

select count(distinct p1.prenom)
from prenoms as p1
join prenoms as p2 on substr(p2.prenom, 1, 10)=p1.prenom
where length(p2.prenom)=16;

select distinct prenom
from prenoms
where substr(prenom, 1, length(prenom)/2) || '-' || substr(prenom, 1, length(prenom)/2) = prenom;
