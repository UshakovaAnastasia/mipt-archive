import pandas
from sklearn.feature_extraction.stop_words import ENGLISH_STOP_WORDS
from nltk.stem.snowball import SnowballStemmer
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report
from sklearn.metrics import accuracy_score
from sklearn.metrics import jaccard_similarity_score
from skmultilearn.problem_transform import LabelPowerset

x = pandas.read_csv('X.txt')
y = pandas.read_csv('Y.txt')
stop = list(set(ENGLISH_STOP_WORDS))  # шумовые слова английского языка
stemmer = SnowballStemmer("english")
stopwords = list(set(ENGLISH_STOP_WORDS))
for w in stopwords:
    w = stemmer.stem(w)
# получить таблицу TF-IDF-значений для слов из описаний сюжетов
tf = TfidfVectorizer(analyzer='word', stop_words=stopwords, min_df=0.005)
x_tf = tf.fit_transform(x.Plot)
plot = pandas.DataFrame(x_tf.todense(), index=x.index, columns=tf.get_feature_names())
hdrs = ['Release Year', 'Origin/Ethnicity', 'Director', 'Cast', 'Title']
for hd in hdrs:
    if hd == 'Title':
        cv = TfidfVectorizer(analyzer='word', stop_words=stopwords)  # TF-IDF для названий
    else:
        cv = CountVectorizer(analyzer='word', min_df=2)  # определить, относится или нет
        # конкретный режиссер (актер, год, страна) к конкретному фильму
    c = cv.fit_transform(x[hd].map(lambda pl: str(pl)))
    p = pandas.DataFrame(c.todense(), index=x.index, columns=cv.get_feature_names())
    plot = pandas.concat([plot, p], axis=1)
x_train, x_test, y_train, y_test = train_test_split(plot, y, test_size=0.33, random_state=42)
classif = LabelPowerset(LogisticRegression())
classif.fit(x_train, y_train)
pr = classif.predict(x_test)
print("Accuracy = ", accuracy_score(y_test, pr))  # доля фильмов, у которых жанры предсказаны абсолюно точно
print("Jaccard similarity score =",
      jaccard_similarity_score(y_test, pr))  # мера схожести исходных и предсказанных наборов жанров
# precision - доля правильных присвоений данного жанра
# recall - способность находить фильмы данного жанра
# f1 - среднее гармоническое precision и recall
# support - количество фильмов каждого жанра в y_test
print(classification_report(y_test, pr, target_names=list(y.head())))
