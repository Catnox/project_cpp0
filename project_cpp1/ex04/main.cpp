#include <iostream>
#include <fstream>
#include <string>

static std::string replaceOccurrences(std::string content, const std::string &s1, const std::string &s2)
{
    size_t pos = 0;
    while ((pos = content.find(s1, pos)) != std::string::npos)
    {
        content.erase(pos, s1.length());
        content.insert(pos, s2);
        pos += s2.length();
    }
    return (content);
}

int main(int argc, char **argv)
{
    // 1. Vérifier qu'on a bien 3 arguments (+ le nom du programme = 4)
    if (argc != 4)
    {
        std::cerr << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
        return (1);
    }

    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    // 2. Vérifier que s1 n'est pas vide
    if (s1.empty())
    {
        std::cerr << "Error: s1 cannot be empty" << std::endl;
        return (1);
    }

    // 3. Ouvrir le fichier source en lecture
    std::ifstream infile(filename.c_str());
    if (!infile.is_open())
    {
        std::cerr << "Error: cannot open file '" << filename << "'" << std::endl;
        return (1);
    }
    if (infile.peek() == std::ifstream::traits_type::eof())
    {
        std::cerr << "Error: file '" << filename << "' is empty" << std::endl;
        infile.close();
        return (1);
    }

    // 4. Créer le fichier de sortie (.replace)
    std::ofstream outfile((filename + ".replace").c_str());
    if (!outfile.is_open())
    {
        std::cerr << "Error: cannot create output file '" << filename << ".replace'" << std::endl;
        infile.close();
        return (1);
    }

    // 5. Lire tout le contenu du fichier
    std::string content;
    std::string line;
    while (std::getline(infile, line))
    {
        content += line;
        if (!infile.eof())
            content += "\n";
    }
    if (infile.bad())
    {
        std::cerr << "Error: failed to read file '" << filename << "'" << std::endl;
        infile.close();
        outfile.close();
        return (1);
    }
    infile.close();

    // 6. Remplacer toutes les occurrences de s1 par s2
    content = replaceOccurrences(content, s1, s2);

    // 7. Écrire dans le fichier de sortie
    outfile << content;
    if (outfile.fail())
    {
        std::cerr << "Error: failed to write to output file" << std::endl;
        outfile.close();
        return (1);
    }
    outfile.close();

    return (0);
}