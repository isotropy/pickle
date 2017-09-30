type contents =
  | String string
  | List (list file)
and file = {
  dir: string,
  filename: string,
  contents
};

type fileSystem = list file;

let fileSystem = [
  {dir: "/", filename: "index.html", contents: String ""},
  {
    dir: "/",
    filename: "services",
    contents:
      List [
        {
          dir: "/",
          filename: "module1.js",
          contents:
            String "import TestModule2 from 'test1/module2';const a = [1,2,3]; document.getElementById('result').innerHTML = 'Hello!'"
        },
        {dir: "test2/", filename: "test2/module1.js", contents: String ""}
      ]
  },
  {
    dir: "/",
    filename: "ui",
    contents:
      List [
        {
          dir: "/",
          filename: "module1.js",
          contents:
            String "import TestModule2 from 'test1/module2';const a = [1,2,3]; document.getElementById('result').innerHTML = 'Hello!'"
        },
        {dir: "test2/", filename: "test2/module1.js", contents: String ""}
      ]
  }
];
