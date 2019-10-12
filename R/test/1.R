d <- mtcars
d$even_gear[d$gear %% 2 == 0] <- 1
d$even_gear[d$gear %% 2 == 1] <- 0
d

