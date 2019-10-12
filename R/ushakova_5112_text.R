generateText=function(alphabet, number){
  ind <- ceiling(runif(number, 0, length(alphabet)))
  vec=vector()
  for (i in ind){
    vec<-c(vec,alphabet[i])
  }
  return (paste (vec, collapse = ''))
}

countWords=function(text, length){
  if (length>nchar(text)){
    return("too long")
  }
  substring<-vector()
  number<-vector()
  arr <- strsplit(text, "")[[1]]
  for (i in 1:(length(arr)-length+1)){
    t<-paste (arr[i:(i+length-1)], collapse = '')
    if (t %in% substring){
      number[match(t,substring)]<-number[match(t,substring)]+1
    } else {
      substring<-c(substring,t)
      number<-c(number,1)
    }
  }
  tab <- data.frame(substring, number)
  return(tab)
}

v<-countWords("abbba",2)
v
t<-generateText(letters, 50)
t

