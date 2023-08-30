au lieu de split au espaces avant l'execution
on va split au espaces avant la redirection

stocker ds un char * le nom de commande
stocker ds un char ** le tableau d'argument
stocker le type de redirection et le nom de fichier dans ce que tu veux (liste chainee etc)


> 1
>> 2
< 3
<< 4

"ls -R > out -l -a < Makefile > out2" -> parse();


"{ls}{-R}{>}{out}{-l}{-a}{<}{Makefile}{>}{out2}"
t_cmd {
	cmd = arg[0]
	arg = {"ls", "-R", "-l" "-a"}
	redir = {1, 3, 1};
	file = {"out", "Makefile", "out2"}
}

"< Makefile cat > out >> append -e" -> parse();
"{<}{Makefile}{cat}{>}{out}{>>}{append}{-e}"
t_cmd {
	cmd = cat
	arg = cat -e
	redir = 1  2
	file = out append
}


ajouter redir new  prend un fichier char et int type >>a modif pour mettre file er type
addback

chevron comp


si echo --> affiche la suite
		si premier caractere == -n ou -nnnnnn
		 		tant que arg = -n ---> debut = apres -n
		afficher tous les arg
		afficher /n

		else
			afficher sans /b






//malloc
//main
	//parseinput
 	parse input (vire espace)  //free
	 data.tab (tab des commande entre pipe)
	 //heredoc
	doc (calloc tab de struct )
				-> doc[i].del (str delimiteur)
	//init struct
	data->pid (tab d int, un fork par commande) //str
	cmd->arg (tab des arg de chaque commande)
	cmd->lst (list file et type (chevron))

 // pipex
			// get cmd (free here)
				//parse
					input (split au espace) //free en fin de fonc
					cmds.arg (calloc tableau avec les cmd)
	//ft_nofork
		`



A FAIRE
	close les here doc a chaque fois que le code quit ou crash malloc
	//close_heredocs(data->docs, data->nb_hd);



pwd << a > fichier --> ca cree plus le fichier
echo << a > fichier  -->

cat << a > 1 || cat << a > 2 || cat << a > 3 --> n ecrit pas dans les 2 dernier fich
//echo << a > lol  -->> pb free  ne creer plus le fichier
echo << test\n
<< "a b"


exit
quit si :
-exit
-exit 'num'
-exit -'num'

quit pas si :
-exit 'num' 'num'
-exit 'num string'
		bash: exit: too many arguments

quit
-exit 'string' '...'
-exit -'string'
-exit: 9223372036854775808 OU  arg = strcomp 7 , 8 ou + 19 chiffre
		bash: exit: a: numeric argument required


tu verifie en premier les arguments
tu print les messages
reviens dans le builtin exit
free
exit

args[i] = "PATH=/bin/"
char *delimiter = strchr("PATH=/bin/", '=');
	delimiter = '=/bin/'
char *name = args[i] = "PATH"
char *value = delimiter + 1;
	value = "/bin/"





	here doc
	ll min pour exit
	ctrl c