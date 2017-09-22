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

## Additional Notes

### Issue and Pull Request Labels

This section lists the labels we use to help us track and manage issues and pull requests. Most labels are used across all Venturesome Stone repositories, but some are specific to `venturesomestone/unsung-anthem`.

[GitHub search](https://help.github.com/articles/searching-issues/) makes it easy to use labels for finding groups of issues or pull requests you’re interested in. For example, you might be interested in [open issues across `venturesomestone/unsung-anthem` and all Venturesome Stone-owned projects which are labeled as bugs, but still need to be reliably reproduced](https://github.com/issues?utf8=%E2%9C%93&q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Abug+label%3Aneeds-reproduction) or perhaps [open pull requests in `venturesomestone/unsung-anthem` which haven’t been reviewed yet](https://github.com/issues?utf8=%E2%9C%93&q=is%3Aopen+is%3Apr+repo%3Aventuresomestone%2Funsung-anthem+comments%3A0). To help you find issues and pull requests, each label is listed with search links for finding open items with that label in `venturesomestone/unsung-anthem` only and also across all Venturesome Stone repositories. We  encourage you to read about [other search filters](https://help.github.com/articles/searching-issues/) which will help you write more focused queries.

The labels are loosely grouped by their purpose, but it’s not required that every issue have a label from every group or that an issue can’t have more than one label from the same group.

Please open an issue on `venturesomestone/unsung-anthem` if you have suggestions for new labels and if you notice some labels are missing on some repositories, please open an issue on that repository.

#### Type of Issue and Issue State

| Label name | `venturesomestone/unsung-anthem` :mag_right: | `venturesomestone`‑org :mag_right: | Description |
| --- | --- | --- | --- |
| `enhancement` | [search][search-anthem-repo-label-enhancement] | [search][search-vs-org-label-enhancement] | Feature requests. |
| `bug` | [search][search-anthem-repo-label-bug] | [search][search-vs-org-label-bug] | Confirmed bugs or reports that are very likely to be bugs. |
| `question` | [search][search-anthem-repo-label-question] | [search][search-vs-org-label-question] | Questions more than bug reports or feature requests (e.g. how do I do X). |
| `feedback` | [search][search-anthem-repo-label-feedback] | [search][search-vs-org-label-feedback] | General feedback more than bug reports or feature requests. |
| `help-wanted` | [search][search-anthem-repo-label-help-wanted] | [search][search-vs-org-label-help-wanted] | The Unsung Anthem team would appreciate help from the community in resolving these issues. |
| `beginner` | [search][search-anthem-repo-label-beginner] | [search][search-vs-org-label-beginner] | Less complex issues which would be good first issues to work on for users who want to contribute to Unsung Anthem. |
| `more-information-needed` | [search][search-anthem-repo-label-more-information-needed] | [search][search-vs-org-label-more-information-needed] | More information needs to be collected about these problems or feature requests (e.g. steps to reproduce). |
| `needs-reproduction` | [search][search-anthem-repo-label-needs-reproduction] | [search][search-vs-org-label-needs-reproduction] | Likely bugs, but haven’t been reliably reproduced. |
| `blocked` | [search][search-anthem-repo-label-blocked] | [search][search-vs-org-label-blocked] | Issues blocked on other issues. |
| `duplicate` | [search][search-anthem-repo-label-duplicate] | [search][search-vs-org-label-duplicate] | Issues which are duplicates of other issues, i.e. they have been reported before. |
| `wontfix` | [search][search-anthem-repo-label-wontfix] | [search][search-vs-org-label-wontfix] | The Unsung Anthem team has decided not to fix these issues for now, either because they’re working as intended or for some other reason. |
| `invalid` | [search][search-anthem-repo-label-invalid] | [search][search-vs-org-label-invalid] | Issues which aren’t valid (e.g. user errors). |

#### Topic Categories

| Label name | `venturesomestone/unsung-anthem` :mag_right: | `venturesomestone`‑org :mag_right: | Description |
| --- | --- | --- | --- |
| `windows` | [search][search-anthem-repo-label-windows] | [search][search-vs-org-label-windows] | Related to Unsung Anthem running on Windows. |
| `linux` | [search][search-anthem-repo-label-linux] | [search][search-vs-org-label-linux] | Related to Unsung Anthem running on Linux. |
| `mac` | [search][search-anthem-repo-label-mac] | [search][search-vs-org-label-mac] | Related to Unsung Anthem running on macOS. |
| `documentation` | [search][search-anthem-repo-label-documentation] | [search][search-vs-org-label-documentation] | Related to any type of documentation (e.g. the [flight manual](https://github.com/venturesomestone/unsung-anthem) (TODO)). |
| `performance` | [search][search-anthem-repo-label-performance] | [search][search-vs-org-label-performance] | Related to performance. |
| `security` | [search][search-anthem-repo-label-security] | [search][search-vs-org-label-security] | Related to security. |
| `ui` | [search][search-anthem-repo-label-ui] | [search][search-vs-org-label-ui] | Related to visual design. |
| `api` | [search][search-anthem-repo-label-api] | [search][search-vs-org-label-api] | Related to Unsung Anthem’s public APIs. |
| `crash` | [search][search-anthem-repo-label-crash] | [search][search-vs-org-label-crash] | Reports of Unsung Anthem completely crashing. |

#### Pull Request Labels

| Label name | `venturesomestone/unsung-anthem` :mag_right: | `venturesomestone`‑org :mag_right: | Description
| --- | --- | --- | --- |
| `work-in-progress` | [search][search-anthem-repo-label-work-in-progress] | [search][search-vs-org-label-work-in-progress] | Pull requests which are still being worked on, more changes will follow. |
| `needs-review` | [search][search-anthem-repo-label-needs-review] | [search][search-vs-org-label-needs-review] | Pull requests which need code review, and approval from the maintainers or Unsung Anthem team. |
| `under-review` | [search][search-anthem-repo-label-under-review] | [search][search-vs-org-label-under-review] | Pull requests being reviewed by the maintainers or Unsung Anthem team. |
| `requires-changes` | [search][search-anthem-repo-label-requires-changes] | [search][search-vs-org-label-requires-changes] | Pull requests which need to be updated based on review comments and then reviewed again. |
| `needs-testing` | [search][search-anthem-repo-label-needs-testing] | [search][search-vs-org-label-needs-testing] | Pull requests which need manual testing. |

[search-anthem-repo-label-enhancement]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Aenhancement
[search-vs-org-label-enhancement]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Aenhancement
[search-anthem-repo-label-bug]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Abug
[search-vs-org-label-bug]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Abug
[search-anthem-repo-label-question]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Aquestion
[search-vs-org-label-question]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Aquestion
[search-anthem-repo-label-feedback]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Afeedback
[search-vs-org-label-feedback]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Afeedback
[search-anthem-repo-label-help-wanted]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Ahelp-wanted
[search-vs-org-label-help-wanted]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Ahelp-wanted
[search-anthem-repo-label-beginner]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Abeginner
[search-vs-org-label-beginner]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Abeginner
[search-anthem-repo-label-more-information-needed]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Amore-information-needed
[search-vs-org-label-more-information-needed]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Amore-information-needed
[search-anthem-repo-label-needs-reproduction]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Aneeds-reproduction
[search-vs-org-label-needs-reproduction]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Aneeds-reproduction

[search-anthem-repo-label-windows]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Awindows
[search-vs-org-label-windows]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Awindows
[search-anthem-repo-label-linux]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Alinux
[search-vs-org-label-linux]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Alinux
[search-anthem-repo-label-mac]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Amac
[search-vs-org-label-mac]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Amac
[search-anthem-repo-label-documentation]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Adocumentation
[search-vs-org-label-documentation]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Adocumentation
[search-anthem-repo-label-performance]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Aperformance
[search-vs-org-label-performance]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Aperformance
[search-anthem-repo-label-security]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Asecurity
[search-vs-org-label-security]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Asecurity
[search-anthem-repo-label-ui]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Aui
[search-vs-org-label-ui]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Aui
[search-anthem-repo-label-api]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Aapi
[search-vs-org-label-api]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Aapi
[search-anthem-repo-label-crash]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Acrash
[search-vs-org-label-crash]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Acrash
[search-anthem-repo-label-blocked]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Ablocked
[search-vs-org-label-blocked]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Ablocked
[search-anthem-repo-label-duplicate]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Aduplicate
[search-vs-org-label-duplicate]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Aduplicate
[search-anthem-repo-label-wontfix]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Awontfix
[search-vs-org-label-wontfix]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Awontfix
[search-anthem-repo-label-invalid]: https://github.com/issues?q=is%3Aopen+is%3Aissue+repo%3Aventuresomestone%2Funsung-anthem+label%3Ainvalid
[search-vs-org-label-invalid]: https://github.com/issues?q=is%3Aopen+is%3Aissue+user%3Aventuresomestone+label%3Ainvalid

[search-anthem-repo-label-work-in-progress]: https://github.com/pulls?q=is%3Aopen+is%3Apr+repo%3Aventuresomestone%2Funsung-anthem+label%3Awork-in-progress
[search-vs-org-label-work-in-progress]: https://github.com/pulls?q=is%3Aopen+is%3Apr+user%3Aventuresomestone+label%3Awork-in-progress
[search-anthem-repo-label-needs-review]: https://github.com/pulls?q=is%3Aopen+is%3Apr+repo%3Aventuresomestone%2Funsung-anthem+label%3Aneeds-review
[search-vs-org-label-needs-review]: https://github.com/pulls?q=is%3Aopen+is%3Apr+user%3Aventuresomestone+label%3Aneeds-review
[search-anthem-repo-label-under-review]: https://github.com/pulls?q=is%3Aopen+is%3Apr+repo%3Aventuresomestone%2Funsung-anthem+label%3Aunder-review
[search-vs-org-label-under-review]: https://github.com/pulls?q=is%3Aopen+is%3Apr+user%3Aventuresomestone+label%3Aunder-review
[search-anthem-repo-label-requires-changes]: https://github.com/pulls?q=is%3Aopen+is%3Apr+repo%3Aventuresomestone%2Funsung-anthem+label%3Arequires-changes
[search-vs-org-label-requires-changes]: https://github.com/pulls?q=is%3Aopen+is%3Apr+user%3Aventuresomestone+label%3Arequires-changes
[search-anthem-repo-label-needs-testing]: https://github.com/pulls?q=is%3Aopen+is%3Apr+repo%3Aventuresomestone%2Funsung-anthem+label%3Aneeds-testing
[search-vs-org-label-needs-testing]: https://github.com/pulls?q=is%3Aopen+is%3Apr+user%3Aventuresomestone+label%3Aneeds-testing

[beginner]:https://github.com/issues?utf8=%E2%9C%93&q=is%3Aopen+is%3Aissue+label%3Abeginner+label%3Ahelp-wanted+user%3Aventuresomestone+sort%3Acomments-desc
[help-wanted]:https://github.com/issues?q=is%3Aopen+is%3Aissue+label%3Ahelp-wanted+user%3Aventuresomestone+sort%3Acomments-desc+-label%3Abeginner
