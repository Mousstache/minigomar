input = [<<]
bash: affiche syntax error

vous: se balade ds le code, ouvre un here_doc, affiche ambigous redirect
****************************************
input = [\t]
bash: absolument rien

vous: se balade ds le code fork etc pour rien, belek ca peut vous niquer a un moment
****************************************
input = [\t|] ou [\t>] etc
bash: affiche syntax error

vous: se balade ds le code
****************************************
input = [> a]
bash: status de retour 0

vous: status inchange ou 127
****************************************
input = [< fichiernonexistant]
bash: status de retour 1

vous: status inchange ou 127
****************************************
