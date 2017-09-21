# Contributing to Unsung Anthem

:+1::tada: First off, thanks for taking the time to contribute! :tada::+1:

These guidelines aren’t ready.

The following is a set of guidelines for contributing to Unsung Anthem. These are mostly guidelines, not rules. Use your best judgment, and feel free to propose changes to this document in a pull request.

#### Table Of Contents

[Code of Conduct](#code-of-conduct)

[How Can I Contribute?](#how-can-i-contribute)
  * [Reporting Bugs](#reporting-bugs)
  * [Suggesting Enhancements](#suggesting-enhancements)
  * [Your First Code Contribution](#your-first-code-contribution)
  * [Pull Requests](#pull-requests)

[Styleguides](#styleguides)
  * [Git Commit Messages](#git-commit-messages)
  * [C++ Styleguide](#c++-styleguide)
  * [Python Styleguide](#python-styleguide)

[Additional Notes](#additional-notes)
  * [Issue and Pull Request Labels](#issue-and-pull-request-labels)

## Code of Conduct

This project and everyone participating in it are governed by the [Unsung Anthem Code of Conduct](CODE_OF_CONDUCT.md). By participating, you’re expected to uphold this code. Please report unacceptable behaviour to [venturesomestone@gmail.com](mailto:venturesomestone@gmail.com).

## How Can I Contribute?

### Reporting Bugs

This section guides you through submitting a bug report for Unsung Athem. Following these guidelines helps the maintainers and the community understand your report :pencil:, reproduce the behaviour :computer: :computer:, and find related reports :mag_right:.

Before creating bug reports, please check [this list](#before-submitting-a-bug-report) as you might find out that you don’t need to create one. When you are creating a bug report, please [include as many details as possible](#how-do-i-submit-a-good-bug-report). Fill out [the required template](ISSUE_TEMPLATE.md), the information it asks for helps us resolve issues faster.

> **Note:** If you find a **Closed** issue that seems like it’s the same thing that you’re experiencing, open a new issue and include a link to the original issue in the body of your new one.

#### Before Submitting A Bug Report

* **Check the [debugging guide](./docs/debugging.md).** You might be able to find the cause of the problem and fix things yourself. Most importantly, check if you can reproduce the problem [in the latest version of Unsung Anthem](./docs/debugging.md#update-to-the-latest-version), if the problem happens when you run Unsung Anthem in [safe mode](./docs/debugging.md#check-if-the-problem-shows-up-in-safe-mode), and if you can get the desired behaviour by changing [the config settings of Unsung Anthem](./docs/debugging.md#check-unsung-anthem-and-package-settings).
* **Check the [FAQs](./docs/faq.md)** for a list of common questions and problems.
* **Perform a [cursory search](https://github.com/issues?q=+is%3Aissue+user%3Aventuresomestone)** to see if the problem has already been reported. If it has **and the issue is still open**, add a comment to the existing issue instead of opening a new one.

#### How Do I Submit A (Good) Bug Report?

Bugs are tracked as [GitHub issues](https://guides.github.com/features/issues/). Just create an issue on the repository and provide the following information by filling in [the template](ISSUE_TEMPLATE.md).

Explain the problem and include additional details to help the maintainers reproduce the problem:

* **Use a clear and descriptive title** for the issue to identify the problem.
* **Describe the exact steps which reproduce the problem** in as many details as possible. For example, start by explaining how you started Unsung Anthem, e.g. which command exactly you used in the terminal, or how you started Unsung Anthem otherwise. When listing steps, **don’t just say what you did, but explain how you did it**. For example, if you moved the cursor to the end of a line, explain if you used the mouse, or a keyboard shortcut or an Unsung Anthem command, and if so which one?
* **Provide specific examples to demonstrate the steps**. Include links to files or GitHub projects, or copy/pasteable snippets, which you use in those examples. If you’re providing snippets in the issue, use [Markdown code blocks](https://help.github.com/articles/markdown-basics/#multiple-lines).
* **Describe the behaviour you observed after following the steps** and point out what exactly is the problem with that behaviour.
* **Explain which behaviour you expected to see instead and why.**
* **Include screenshots and animated GIFs** which show you following the described steps and clearly demonstrate the problem. (TODO include instructions for including the input recording here.) You can use [this tool](http://www.cockos.com/licecap/) to record GIFs on macOS and Windows and [this tool](https://github.com/colinkeenan/silentcast) or [this tool](https://github.com/GNOME/byzanz) on Linux.
* **If you’re reporting that Unsung Anthem crashed**, include a crash report from the operating system. On macOS, the crash report will be available in `Console.app` under "Diagnostic and usage information" > "User diagnostic reports". Include the crash report in the issue in a [code block](https://help.github.com/articles/markdown-basics/#multiple-lines), a [file attachment](https://help.github.com/articles/file-attachments-on-issues-and-pull-requests/), or put it in a [gist](https://gist.github.com/) and provide link to that gist.
* **If the problem is related to performance or memory**, include a [CPU profile capture](./docs/debugging.md#diagnose-runtime-performance) with your report.
* **If the problem wasn’t triggered by a specific action**, describe what you were doing before the problem happened and share more information using the guidelines below.

Provide more context by answering these questions:

* **Can you reproduce the problem in [safe mode](./docs/debugging.md#diagnose-runtime-performance-problems-with-the-dev-tools-cpu-profiler)?**
* **Did the problem start happening recently** (e.g. after updating to a new version of Unsung Anthem) or was this always a problem?
* If the problem started happening recently, **can you reproduce the problem in an older version of Unsung Anthem?** What’s the most recent version in which the problem doesn’t happen? You can download older versions of Unsung Anthem from [the releases page](https://github.com/venturesomestone/unsung-anthem/releases).
* **Can you reliably reproduce the issue?** If not, provide details about how often the problem happens and under which conditions it normally happens.

Include details about your configuration and environment:

* **Which version of Unsung Anthem are you using?** You can get the exact version by running `anthem -v` in your terminal.
* **What’s the name and version of the OS you’re using**?
* **Are you running Unsung Anthem in a virtual machine?** If so, which VM software are you using and which operating systems and versions are used for the host and the guest?
* **Which keyboard layout are you using?** Are you using a US layout or some other layout?

### Suggesting Enhancements

This section guides you through submitting an enhancement suggestion for Unsung Anthem, including completely new features and minor improvements to existing functionality. Following these guidelines helps the maintainers and the community understand your suggestion :pencil: and find related suggestions :mag_right:.

Before creating enhancement suggestions, please check [this list](#before-submitting-an-enhancement-suggestion) as you might find out that you don’t need to create one. When you are creating an enhancement suggestion, please [include as many details as possible](#how-do-i-submit-a-good-enhancement-suggestion). Fill in [the template](ISSUE_TEMPLATE.md), including the steps that you imagine you would take if the feature you’re requesting existed.

#### Before Submitting An Enhancement Suggestion

* **Check the [debugging guide](./docs/debugging.md)** for tips – you might discover that the enhancement is already available. Most importantly, check if you’re using [the latest version of Unsung Anthem](./docs/debugging.md#update-to-the-latest-version) and if you can get the desired behaviour by changing [the config settings of Unsung Anthem](./docs/debugging.md#check-unsung-anthem-and-package-settings).
* **Perform a [cursory search](https://github.com/issues?q=+is%3Aissue+user%3Aventuresomestone)** to see if the enhancement has already been suggested. If it has, add a comment to the existing issue instead of opening a new one.

#### How Do I Submit A (Good) Enhancement Suggestion?

Enhancement suggestions are tracked as [GitHub issues](https://guides.github.com/features/issues/). Just create an issue on that repository and provide the following information:

* **Use a clear and descriptive title** for the issue to identify the suggestion.
* **Provide a step-by-step description of the suggested enhancement** in as many details as possible.
* **Provide specific examples to demonstrate the steps**. Include copy/pasteable snippets which you use in those examples, as [Markdown code blocks](https://help.github.com/articles/markdown-basics/#multiple-lines).
* **Describe the current behaviour** and **explain which behaviour you expected to see instead** and why.
* **Include screenshots and animated GIFs** which help you demonstrate the steps or point out the part of Unsung Anthem which the suggestion is related to. You can use [this tool](http://www.cockos.com/licecap/) to record GIFs on macOS and Windows, and [this tool](https://github.com/colinkeenan/silentcast) or [this tool](https://github.com/GNOME/byzanz) on Linux.
* **Specify which version of Unsung Anthem you’re using.** You can get the exact version by running `anthem -v` in your terminal.
* **Specify the name and version of the OS you’re using.**

### Your First Code Contribution

Unsure where to begin contributing to Unsung Anthem? You can start by looking through these `beginner` and `help-wanted` issues:

* [Beginner issues][beginner] - issues which should only require a few lines of code and a test or two.
* [Help wanted issues][help-wanted] - issues which should be a bit more involved than `beginner` issues.

Both issue lists are sorted by total number of comments. While not perfect, number of comments is a reasonable proxy for impact a given change will have.

If you want to read about using Unsung Anthem, the [Unsung Anthem Flight Manual](https://github.com/venturesomestone/unsung-anthem) is free and available online. You can find the source to the manual in [TODO](https://github.com/venturesomestone/unsung-anthem). (TODO: Think about changing the name.)

### Pull Requests

* Fill in [the required template](PULL_REQUEST_TEMPLATE.md)
* Do not include issue numbers in the pull request title
* Include screenshots and animated GIFs in your pull request whenever possible
* Follow the [C++](#c++-styleguide) or [Python](#python-styleguide) styleguides.
* Include thoughtfully-worded, well-structured [Catch](https://github.com/philsquared/Catch) tests in the `./test` directory. Run them using the build script (TODO: Add a link to some instructions on using the build script)
* Document new code based on the [Documentation Styleguide](#documentation-styleguide) (TODO)
* End all files with a newline
* Avoid platform-dependent code (TODO: Maybe add some guidelines.)

## Styleguides

### Git Commit Messages

* Use the present tense ("Add feature" not "Added feature")
* Use the imperative mood ("Move cursor to..." not "Moves cursor to...")
* Limit the first line to 72 characters or less
* Reference issues and pull requests liberally after the first line
* When only changing documentation, include `[ci skip]` in the commit description
* Consider starting the commit message with an applicable emoji:
    * :art: `:art:` when improving the format/structure of the code
    * :racehorse: `:racehorse:` when improving performance
    * :non-potable_water: `:non-potable_water:` when plugging memory leaks
    * :memo: `:memo:` when writing docs
    * :penguin: `:penguin:` when fixing something on Linux
    * :apple: `:apple:` when fixing something on macOS
    * :checkered_flag: `:checkered_flag:` when fixing something on Windows
    * :bug: `:bug:` when fixing a bug
    * :fire: `:fire:` when removing code or files
    * :green_heart: `:green_heart:` when fixing the CI build
    * :white_check_mark: `:white_check_mark:` when adding tests
    * :lock: `:lock:` when dealing with security
    * :arrow_up: `:arrow_up:` when upgrading dependencies
    * :arrow_down: `:arrow_down:` when downgrading dependencies
    * :shirt: `:shirt:` when removing linter warnings
