'''
    - Martes, 5 de enero del 2021 [12:36 AM]
    - TERMINADO: [01:11 AM] (TENÍA ERRORES)

    - TERMINADO FINAL (COPIANDO REFERENCIA AL PORTAPAPELES Y TODO): [02:17 AM]

    Programa para obtener la referencia bibliográfica siguiendo el formato
    que el profe nos indicó:

    - Página Web:
        Autor, “Nombre de la página”. Dirección Web completa, Año
        Ejemplo: R. Smith, “Open dynamics engine.” http://www.ode.org, 2007

    - Libro:
        Autor(es), Nombre. Editorial, Año de Edición.
        Ejemplo: J. Findlay and I. Gilchrist, Active Vision. Oxford: Oxford Univ. Press, 2003

    Desde la terminal se recibirán los argumentos:
        programa.py
        [1er argumento]: "Libro" o "Web". Deberá ser con minúsculas, aunque
            lo puedo hacer case-insensitive.

            - FUENTE: How do I do a case-insensitive string comparison?
                https://stackoverflow.com/questions/319426/how-do-i-do-a-case-insensitive-string-comparison

        [2do argumento]: Autor(es), separados por comas, y entre comillas:
            "Alejando B., Javier H."

        [3er argumento]: Nombre de la página web o del libro.

        [4to argumento]:
            - Si es página web: Dirección web completa.
            - Si es libro: Editorial

        [5to argumento]: Año
'''

# Para recibir argumentos.
import sys
# Para guardar la cadena de referencia en el portapapeles.
'''
    - TUVE QUE INSTALAR EL MÓDULO CON EL COMANDO:

        pip install pyperclip

    - SITIO WEB: https://pypi.org/project/pyperclip/
'''
import pyperclip

def main():
    if not is_there_enough_args(sys.argv):
        return 0

    print("\n - REFERENCIA: ")

    reference = generate_reference(sys.argv)
    print("\n", reference, "\n")

    '''
     COPIAR LA CADENA RESULTANTE EN EL PORTAPAPELES:

     FUENTE: Python script to copy text to clipboard [duplicate]
        https://stackoverflow.com/questions/11063458/python-script-to-copy-text-to-clipboard

    - TUVE QUE INSTALAR EL MÓDULO CON EL COMANDO:

        pip install pyperclip

    - SITIO WEB: https://pypi.org/project/pyperclip/

        import pyperclip
        pyperclip.copy('The text to be copied to the clipboard.') # COPIAR
        spam = pyperclip.paste() # PEGAR
    '''
    pyperclip.copy(reference)

    return 1

# Genera la referencia
'''
    [1er argumento]: "Libro" o "Web". Deberá ser con minúsculas, aunque
        lo puedo hacer case-insensitive.

        - FUENTE: How do I do a case-insensitive string comparison?
            https://stackoverflow.com/questions/319426/how-do-i-do-a-case-insensitive-string-comparison

    [2do argumento]: Autor(es), separados por comas, y entre comillas:
        "Alejando B., Javier H."

    [3er argumento]: Nombre de la página web o del libro.

    [4to argumento]:
        - Si es página web: Dirección web completa.
        - Si es libro: Editorial

    [5to argumento]: Año

    ----------------------------------------------------------------------------
    COMPARACIÓN CASE-INSENSITIVE ASUMIENDO CADENAS ASCII
        string1 = 'Hello'
        string2 = 'hello'

        if string1.lower() == string2.lower():
            print("The strings are the same (case insensitive)")
        else:
            print("The strings are NOT the same (case insensitive)")
'''
def generate_reference(args_list):
    book_or_web = args_list[1]
    authors = args_list[2]
    name = args_list[3]
    # Argumento 4: Dirección web o editorial.

    # Si year es solo espacios
    '''
    FUENTE: Check if string contains only whitespace
        https://stackoverflow.com/questions/2405292/check-if-string-contains-only-whitespace

    -> Use the str.isspace() method:

        Return True if there are only whitespace characters in the string and there is at least one character, False otherwise.

        A character is whitespace if in the Unicode character database (see unicodedata), either its general category is Zs (“Separator, space”), or its bidirectional class is one of WS, B, or S.
    '''
    if(args_list[5].isspace()):
        year = "(s. f.)"
    else:
        year = args_list[5]

    # Inicializar la cadena de la referencia.
    # Si autor no es solo espacios
    if(authors.isspace()):
        reference = ""
    else:
        reference = authors + ", "

    # Referencia web.
    if(book_or_web.lower() == "web".lower()):
        '''
            - Página Web:
                Autor, “Nombre de la página”. Dirección Web completa, Año
        '''
        webpage_url = args_list[4]
        reference += "\"" + name + "\". " + webpage_url

    elif(book_or_web.lower() == "libro".lower()):
        editorial = args_list[4]
        '''
            - Libro:
                Autor(es), Nombre. Editorial, Año de Edición.
                Ejemplo: J. Findlay and I. Gilchrist, Active Vision. Oxford: Oxford Univ. Press, 2003
        '''
        reference += name + ". " + editorial
    # Si no dice "web" ni "libro", indicarlo y terminar programa.
    else:
        print("\n - NO SE INDICÓ SI ERA PÁGINA WEB O LIBRO -\n")
        return "ERROR" # ERROR

    reference += ", " + year

    return reference

# Revisa si los argumentos son correctos
def is_there_enough_args(args_list):
    # Si hay más o menos argumentos.
    if(len(args_list) != 6):
        print("\n\nNo se recibieron los argumentos necesarios (6).", end="\n")
        if(len(args_list) == 1):
            print(" - Se recibió 1 argumento:\n")
        else:
            print(" - Se recibieron [{}] argumentos:\n".format(len(args_list)))
        print(args_list)
        print("\n - USO: {} <\"libro\" o \"web\"> <\"autor(es)\ separados por comas\"> <nombre página web o del libro> <dirección web completa o editorial> <Año>".format(args_list[0]), end="\n\n")
        return False
    return True

if __name__ == "__main__":
    main()
