#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function prototypes */
int validation_octet(char *octet);
int validation_ip(char *ip);
char* obtenir_classe_ip(int premier_octet);

int main() {
    char *data;
    char ip[16];
    int premier_octet;

    // Print the HTTP header
    printf("Content-Type: text/html\n\n");

    // Get the IP address from the query string
    data = getenv("QUERY_STRING");
    if (data != NULL) {
        // Extract IP address from the query string
        if (sscanf(data, "ip=%15s", ip) == 1) {
            // Generate HTML content
            printf("<!DOCTYPE html>\n");
            printf("<html lang=\"fr\">\n");
            printf("<head>\n");
            printf("    <meta charset=\"UTF-8\">\n");
            printf("    <title>Résultat de la Vérification d'Adresse IP</title>\n");
            printf("    <style>\n");
            printf("        body {\n");
            printf("            margin: 0;\n");
            printf("            padding: 0;\n");
            printf("            overflow: hidden;\n");
            printf("            background-color: black;\n");
            printf("            color: white;\n");
            printf("            font-family: monospace;\n");
            printf("            font-size: 16px;\n");
            printf("        }\n");
            printf("        @keyframes changement_fond {\n");
            printf("            0%% { background-color: black; }\n");
            printf("            50%% { background-color: #333; }\n");
            printf("            100%% { background-color: black; }\n");
            printf("        }\n");
            printf("        body {\n");
            printf("            animation: changement_fond 10s infinite;\n");
            printf("        }\n");
            printf("        .animation-texte {\n");
            printf("            font-size: 24px;\n");
            printf("            animation: changement_couleur_texte 3s infinite, agrandissement 2s infinite;\n");
            printf("        }\n");
            printf("        @keyframes changement_couleur_texte {\n");
            printf("            0%% { color: red; }\n");
            printf("            25%% { color: yellow; }\n");
            printf("            50%% { color: lime; }\n");
            printf("            75%% { color: cyan; }\n");
            printf("            100%% { color: red; }\n");
            printf("        }\n");
            printf("        @keyframes agrandissement {\n");
            printf("            0%% { font-size: 24px; }\n");
            printf("            50%% { font-size: 36px; }\n");
            printf("            100%% { font-size: 24px; }\n");
            printf("        }\n");
            printf("        input[type=\"submit\"] {\n");
            printf("            font-size: 16px;\n");
            printf("            padding: 10px 20px;\n");
            printf("            background-color: #4CAF50;\n");
            printf("            color: white;\n");
            printf("            border: none;\n");
            printf("            cursor: pointer;\n");
            printf("            transition: background-color 0.3s;\n");
            printf("        }\n");
            printf("        input[type=\"submit\"]:hover {\n");
            printf("            background-color: #45a049;\n");
            printf("        }\n");
            printf("    </style>\n");
            printf("</head>\n");
            printf("<body>\n");
            printf("    <form action=\"/cgi-bin/verif_ip.cgi\" method=\"get\">\n");
            printf("        <label class=\"animation-texte\" for=\"ip\">Entrez une adresse IP :</label>\n");
            printf("        <input type=\"text\" id=\"ip\" name=\"ip\" value=\"%s\">\n", ip);
            printf("        <input type=\"submit\" value=\"Vérifier\">\n");
            printf("    </form>\n");
            printf("    <div>\n");
            if (validation_ip(ip)) {
                sscanf(ip, "%d", &premier_octet);
                printf("        <p class=\"animation-texte\">L'adresse IP %s est valide et appartient à %s</p>\n", ip, obtenir_classe_ip(premier_octet));
            } else {
                printf("        <p class=\"animation-texte\">L'adresse IP %s n'est pas valide.</p>\n", ip);
            }
            printf("    </div>\n");
            printf("</body>\n");
            printf("</html>\n");
        }
    }
    return 0;
}

int validation_octet(char *octet) {
    int nombre = atoi(octet);
    if (nombre >= 0 && nombre <= 255) {
        return 1; 
    }
    return 0;  
}

int validation_ip(char *ip) {
    char *segment;
    int points = 0;
    char ip_copie[16];
    strcpy(ip_copie, ip);
    segment = strtok(ip_copie, ".");
    while (segment != NULL) {
        if (!validation_octet(segment)) {
            return 0;  
        }
        segment = strtok(NULL, ".");
        points++;
    }
    return (points == 4);
}

char* obtenir_classe_ip(int premier_octet) {
    if (premier_octet >= 0 && premier_octet <= 127) {
        return "Classe A";
    } else if (premier_octet >= 128 && premier_octet <= 191) {
        return "Classe B";
    } else if (premier_octet >= 192 && premier_octet <= 223) {
        return "Classe C";
    } else if (premier_octet >= 224 && premier_octet <= 239) {
        return "Classe D (Multicast)";
    } else if (premier_octet >= 240 && premier_octet <= 255) {
        return "Classe E (Expérimental)";
    } else {
        return "Incorrect";
    }
}
