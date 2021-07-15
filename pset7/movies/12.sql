SELECT title FROM movies WHERE id in (
SELECT movie_id FROM stars JOIN people on people.id = stars.person_id WHERE name == "Johnny Depp"
INTERSECT
SELECT movie_id FROM stars JOIN people on people.id = stars.person_id WHERE name == "Helena Bonham Carter");