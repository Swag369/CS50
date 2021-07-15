SELECT DISTINCT name FROM movies JOIN stars on stars.movie_id = movies.id JOIN people ON people.id=stars.person_id WHERE year==2004 ORDER BY birth;
