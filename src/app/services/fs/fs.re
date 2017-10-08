type contents =
  | String string
  | List (list file)
and file = {
  id: int,
  dir: string,
  filename: string,
  contents
};

type fileSystem = list file;

let fileSystem = [
  {
    id: 1,
    dir: "/",
    filename: "index.js",
    contents: String "export default class Test {print() {console.log('printed')};}"
  },
  {
    id: 2,
    dir: "/",
    filename: "module1.js",
    contents: String "export default class Module1 {print() {console.log('module1')};}"
  },
  {
    id: 3,
    dir: "/",
    filename: "module2.js",
    contents: String "export default class Module2 {print() {console.log('module2')};}"
  },
  {
    id: 4,
    dir: "/",
    filename: "module3.js",
    contents: String "export default class Module3 {print() {console.log('module3')};}"
  },
  {
    id: 5,
    dir: "/",
    filename: "services",
    contents:
      List [
        {
          id: 6,
          dir: "/",
          filename: "module1.js",
          contents:
            String "import TestModule2 from 'test1/module2';const a = [1,2,3]; document.getElementById('result').innerHTML = 'Hello!'"
        },
        {id: 7, dir: "test2/", filename: "test2/module1.js", contents: String ""}
      ]
  },
  {
    id: 8,
    dir: "/",
    filename: "ui",
    contents:
      List [
        {
          id: 9,
          dir: "/",
          filename: "module1.js",
          contents:
            String "import TestModule2 from 'test1/module2';const a = [1,2,3]; document.getElementById('result').innerHTML = 'Hello!'"
        },
        {id: 10, dir: "test2/", filename: "test2/module1.js", contents: String ""}
      ]
  }
];
