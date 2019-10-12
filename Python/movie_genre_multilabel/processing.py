from nltk.stem.snowball import SnowballStemmer
import pandas
import re


# genres.txt - файл с жанрами фильмов, release_origin_director_cast.csv - с годом, страной, режиссером и актерами
# (эти файлы были заранее избавлены от лишних слов, примечаний, переносов строки и т. д. с использованием регулярных
#  выражений).
# wikiplots.txt - файл со всеми данными по фильмам.
# В результате работы программы получаются файлы X.txt и Y.txt, которые используются в main.py.

def clean(s):  # заменить написание через дефис на слитное, оставить только буквы и заменить их на строчные
    s = s.lower()
    s = s.replace('-', '')
    s = re.sub('\W', ' ', s)
    s = re.sub('\s{2,}', ' ', s)
    s = s.strip(' ')
    return s


stemmer = SnowballStemmer("english")  # для нахождения основы слов
data = pandas.read_csv('wikiplots.txt')
data['Plot'] = data['Plot'].map(lambda pl: clean(pl))
data['Title'] = data['Title'].map(lambda pl: clean(pl))
data['Plot'] = data.Plot.map(lambda x: ' '.join([stemmer.stem(y) for y in x.split(' ')]))
data['Title'] = data.Title.map(lambda x: ' '.join([stemmer.stem(y) for y in x.split(' ')]))
rel_orig_dir_cast = pandas.read_csv('release_origin_director_cast.csv')
hdrs = ['Origin/Ethnicity', 'Director', 'Cast']
for hdr in hdrs:  # например, "James Smith, Jane Smith" -> "jamessmith janesmith"
    rel_orig_dir_cast[hdr] = rel_orig_dir_cast[hdr].map(lambda pl: str(pl))
    rel_orig_dir_cast[hdr] = rel_orig_dir_cast[hdr].str.lower()
    rel_orig_dir_cast[hdr] = rel_orig_dir_cast[hdr].str.replace(' ', '', regex=False)
    rel_orig_dir_cast[hdr] = rel_orig_dir_cast[hdr].str.replace(',', ' ', regex=False)
    rel_orig_dir_cast[hdr] = rel_orig_dir_cast[hdr].str.replace('^nan$', '')
gen = pandas.read_csv('genres.txt')
gen['Genre'] = gen['Genre'].map(lambda gg: set(gg.split()))
genres = {'kids/family', 'war', 'thriller', 'western', 'mystery', 'action/adventure', 'fantasy/folklore',
          'romance', 'unknown', 'crime', 'history', 'drama', 'comedy', 'horror', 'short',
          'animation/anime', 'musical/dance', 'sport', 'sci-fi', 'spy'}  # список жанров
d = dict()
for g in genres:
    d[g] = []
for g in genres:
    for v in gen['Genre'].values:
        if g in v:
            d[g].append(1)
        else:
            d[g].append(0)
y = pandas.DataFrame.from_dict(d)  # 1 - если является фильмом данного жанра, 0 - в противном случае
result = pandas.concat([data[['Title']], rel_orig_dir_cast, data[['Plot']]], axis=1)
for i in range(len(y.index)):  # исключить фильмы неизвестного жанра
    if y['unknown'][i] == 1:
        y = y.drop(i)
        result = result.drop(i)
y = y.drop(columns='unknown')
result.to_csv('X.txt', index=False)
y.to_csv('Y.txt', index=False)
