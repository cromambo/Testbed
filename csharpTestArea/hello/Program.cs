using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Xml;
using System.Xml.Linq;

namespace hello
{
    class Program
    {
        static void Main(string[] args)
        {
            //TestOutArrays();

            //PersonTest();
            xmltest tester = new xmltest();

            Console.WriteLine("Reader");
            WriteRecipeToConsole(tester.GetRecipeListByReader());

            Console.WriteLine("XMLDom");
            WriteRecipeToConsole(tester.GetRecipeListByXmlDom());

            //List<Recipe> reader = tester.GetRecipeListByReader();
            //List<Recipe> dom = tester.GetRecipeListByXmlDom();
            //if(reader == dom)
            //    Console.WriteLine("equal");

            Console.WriteLine("XDoc");
            WriteRecipeToConsole(tester.GetRecipeListByXDoc());

            Console.ReadLine();
        }

        public static void WriteRecipeToConsole(List<Recipe> list)
        {
            foreach (Recipe rec in list)
            {
                Console.WriteLine(rec.Title);
                foreach (string item in rec.Items)
                {
                    Console.WriteLine(item);
                }
            }
        }

        private static void TestOutArrays()
        {
            ArrayTest t = new ArrayTest();
            t.TestSomeArrays();
        }

        private static void PersonTest()
        {
            Person p = new Person();
            p.Name = "Joe";
            p.Age = 10;
            Console.WriteLine(p);
        }
    }
    public class Recipe
    {
        public List<string> Items;
        public string Title { get; set; }
        public Recipe()
        {
            Items = new List<string>();
        }
    }
    public class xmltest
    {
        public List<Recipe> GetRecipeListByReader()
        {
            List<Recipe> recipelist = new List<Recipe>();
            string inputfilename = "RecipeInput.xml";
            if (File.Exists(inputfilename))
            {
                using (FileStream fs = File.OpenRead(inputfilename))
                {
                    using (XmlReader reader = XmlReader.Create(fs))
                    {
                        reader.ReadToFollowing("Cookbook");


                        while (reader.ReadToFollowing("Recipe")) //this doesnt get the second recipe, why?
                        {
                            Recipe newRecipe = new Recipe();
                            List<string> items = new List<string>();

                            newRecipe.Title = reader.GetAttribute("Title");

                            reader.ReadToDescendant("Ingredients");
                            reader.ReadToDescendant("Item"); //what if there are no items?
                            do
                            {
                                string newItem = reader.ReadElementContentAsString();
                                items.Add(newItem);

                            } while (reader.ReadToNextSibling("Item"));

                            newRecipe.Items = items;

                            recipelist.Add(newRecipe);
                        }
                    }
                }
            }
            return recipelist;
        }
        public List<Recipe> GetRecipeListByXmlDom()
        {
            List<Recipe> recipelist = new List<Recipe>();
            string inputfilename = "RecipeInput.xml";
            if (File.Exists(inputfilename))
            {
                string inputDocContents = File.ReadAllText(inputfilename);
              
                XmlDocument doc = new XmlDocument();

                doc.LoadXml(inputDocContents);
                XmlNode cookbook = doc.SelectSingleNode("Cookbook");
                XmlNodeList recipeNodes = cookbook.SelectNodes("./Recipe");
                if (recipeNodes.Count > 0)
                {
                    foreach (XmlNode node in recipeNodes)
                    {
                        Recipe newRecipe = new Recipe();
                        newRecipe.Title = node.Attributes.GetNamedItem("Title").Value;
                        newRecipe.Items = new List<string>();
                        foreach (XmlNode item in node.SelectNodes("./Ingredients/Item"))
                        {
                            newRecipe.Items.Add(item.InnerText);
                        }
                        recipelist.Add(newRecipe);
                    }
                }
            }

            return recipelist;
        }

        public List<Recipe> GetRecipeListByXDoc()
        {
            List<Recipe> recipelist = new List<Recipe>();
            string inputfilename = "RecipeInput.xml";

            if (File.Exists(inputfilename))
            {
                XDocument doc = XDocument.Load(inputfilename);
                foreach (XElement recipeElement in doc.Descendants("Recipe"))
                {
                    Recipe newRecipe = new Recipe();
                   // newRecipe.Items = new List<string>();
                    newRecipe.Title = recipeElement.Attribute("Title").Value;

                    foreach (XElement item in recipeElement.Descendants("Item"))
                    {
                        newRecipe.Items.Add(item.Value);
                    }



                    recipelist.Add(newRecipe);
                }
            }

            return recipelist;
        }
    }
    class Person
    {
        private int myAge;


        public int Age
        {
            get { return myAge; }
            set { myAge = value; }
        }
        private String myName;

        public String Name
        {
            get { return myName; }
            set { myName = value; }
        }

        public override string ToString()
        {
            return "Name = " + Name + "Age =" + Age;
        }


    }
    class ArrayTest
    {
        public ArrayTest()
        {
            Console.WriteLine("ArrayTest Constructor");
        }

        public void TestSomeArrays()
        {
            String[] fingers = new String[] { "Thumb", "Fore", "Middle", "Ring", "Pinkie" };
            for (int i = 0; i < fingers.Length; i++)
            {
                Console.Write("{0} ", fingers[i]);
            }

            int[,] multidim = new int[,] { { 1, 1 }, { 2, 2 } };

            foreach (int item in multidim)
            {
                Console.WriteLine(item);
            }

            char[] chararray = { 'a' };
            foreach (char character in chararray)
            {
                Console.WriteLine(character);
            }
            fingers[2] = "addition";
            Console.WriteLine(fingers[2]);
            try
            {
                Console.WriteLine(multidim[3, 3]);

            }
            catch (Exception ex)
            {
                Console.WriteLine("exception found");
                Console.WriteLine(ex.ToString());
            }

        }

    }
}
