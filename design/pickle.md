# Isotropy IDE 

The Isotropy IDE lets you edit JavaScript inside a browser, and deploy it to supported cloud platforms.

## Third Party Components

1. GitLab (we're going to use this a the git backend.)
 

## How does the IDE look?

The IDE would look exactly like VS Code. 

<img alt="IDE UI" src="https://dl.dropboxusercontent.com/s/j1hab8h4fh9dkb7/IMG_20170910_114115_01.jpg" style="max-width: 800px" />

We have 5 panes
1. Left menu strip
2. File Tree View
3. Editor
4. Console (where you can see log messages etc)
5. Status bar

## Instantiating the IDE

The IDE can be imported into any React project. Should be available on npm.

```js
import ide from "isotropy-ide";
```

The editor can be created in one of two ways:

```js
//Without a git url
const instance = ide(containerElement);

//With a git url
const instance = ide("url/to/repo", containerElement);
```

If the IDE is called without a git url, we overlay with a bunch of templates
- Empty project (selected)
- A todo list
- A personal info manager
- ^ All are examples...

Ask the user to name the project. And then we'll automatically create a repo on our own servers.
We'll use GitLab Open Source edition for this. 

```js
//sourceCode is an object containing an array of files.
//Something like { name: "todo-list", url: "giturl", files: [...] }
const sourceCode = await templateService.get("todo-list"); //based on selection
git.createRepository(projectName, sourceCode)
//Show loading bars...
ide.load(sourceCode);
```
If the IDE is created with a git url, we open the selected project.

```js
const sourceCode = await gitService.get(url);
ide.load(sourceCode);
```

## Deployment

```js
const config = { domainType: "sub-domain", name: "hello-world", provider: "isotropy-lambda" };
const appId = await deploymentService.deploy(projectName, config);
```

