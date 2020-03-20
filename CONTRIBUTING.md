# Contributing to Obliging Ode and Unsung Anthem

:+1::tada: First off, thanks for taking the time to contribute! :tada::+1:

There are many ways in which you can contribute, beyond writing code. The goal of this document is to provide a high-level overview of how you can get involved.

The following is a set of guidelines for contributing to Obliging Ode and Unsung Anthem. These are mostly guidelines, not rules. Use your best judgment and feel free to propose changes to this document in a pull request.

#### Table of Contents

[Code of Conduct](#code-of-conduct)

[How Can I Contribute?](#how-can-i-contribute)
  * [Reporting Bugs](#reporting-bugs)
  * [Suggesting Enhancements](#suggesting-enhancements)
  * [Your First Code Contribution](#your-first-code-contribution)
  * [Pull Requests](#pull-requests)

[Style Guides](#style-guides)
  * [Git Commit Messages](#git-commit-messages)
  * [C++ Style Guide](#c-style-guide)
  * [Python Style Guide](#python-style-guide)
  * [Documentation Style Guide](#documentation-style-guide)

## Code of Conduct

This project and everyone participating in it are governed by the [Contributor Covenant Code of Conduct](CODE_OF_CONDUCT.md). By participating, you’re expected to uphold this code. Please report unacceptable behaviour to antti.kivi@visiosto.fi.

## How Can I Contribute?

### Reporting Bugs

This section guides you through submitting a bug report for Obliging Ode and Unsung Anthem. Following these guidelines helps the maintainers and the community understand your report :pencil:, reproduce the behaviour :computer: :computer:, and find related reports :mag_right:.

Before creating bug reports, please check [this list](#before-submitting-a-bug-report) as you might find out that you don’t need to create one. When you are creating a bug report, please [include as many details as possible](#how-do-i-submit-a-good-bug-report). Fill out [the required template](.github/ISSUE_TEMPLATE/bug_report.md), the information it asks for helps us resolve issues faster.

> **Note:** If you find a **Closed** issue that seems like it’s the same thing that you’re experiencing, open a new issue and include a link to the original issue in the body of your new one.

#### Before Submitting a Bug Report

* **Check the [debugging guide](#).** You might be able to find the cause of the problem and fix things yourself. Most importantly, check if you can reproduce the problem [in the latest version of Obliging Ode and Unsung Anthem](#).
* **Check the [FAQ](#)** for a list of common questions and problems.
* **Perform a [cursory search](https://github.com/issues?q=is%3Aissue+user%3Aanttikivi)** to see if the problem has already been reported. If it has and the issue is still open, add a comment to the existing issue instead of opening a new one.

#### How Do I Submit a (Good) Bug Report?

Bugs are tracked as [GitHub issues](https://guides.github.com/features/issues). Just create an issue on the repository and provide the following information by filling in [the template](.github/ISSUE_TEMPLATE/bug_report.md).

Explain the problem and include additional details to help the maintainers reproduce the problem:

* **Use a clear and descriptive title** for the issue to identify the problem.
* **Describe the exact steps which reproduce the problem** in as many details as possible. For example, start by explaining how you started Unsung Anthem, e.g. which command exactly you used in the terminal or how you started Unsung Anthem otherwise. When listing steps, **don’t just say what you did, but explain how you did it**. For example, if you moved the cursor to the end of a line, explain if you used the mouse, or a keyboard shortcut or an Unsung Anthem command, and if so which one?
* **Provide specific examples to demonstrate the steps**. Include links to files or GitHub projects, or copiable snippets, which you use in those examples. If you’re providing snippets in the issue, use [Markdown code blocks](https://help.github.com/articles/markdown-basics#multiple-lines).
* **Describe the behaviour you observed after following the steps** and point out what exactly is the problem with that behaviour.
* **Explain which behaviour you expected to see instead and why.**
* **Include screenshots and animated GIFs** which show you following the described steps and clearly demonstrate the problem. (TODO include instructions for including the input recording here.) You can use [this tool](http://www.cockos.com/licecap) to record GIFs on macOS and Windows and [this tool](https://github.com/colinkeenan/silentcast) or [this tool](https://github.com/GNOME/byzanz) on Linux.
* **If you’re reporting that Obliging Ode or Unsung Anthem crashed**, include a crash report from the operating system. On macOS, the crash report will be available in `Console.app` under ‘Diagnostic and usage information’ > ‘User diagnostic reports’. Include the crash report in the issue in a [code block](https://help.github.com/articles/markdown-basics#multiple-lines), a [file attachment](https://help.github.com/articles/file-attachments-on-issues-and-pull-requests), or put it in a [gist](https://gist.github.com) and provide link to that gist.
* **If the problem is related to performance or memory**, include a [CPU profile capture](#) with your report.
* **If the problem wasn’t triggered by a specific action**, describe what you were doing before the problem happened and share more information using the guidelines below.

Provide more context by answering these questions:

* **Did the problem start happening recently** (e.g. after updating to a new version of Obliging Ode or Unsung Anthem) or was this always a problem?
* If the problem started happening recently, **can you reproduce the problem in an older version of Obliging Ode or Unsung Anthem?** What’s the most recent version in which the problem doesn’t happen? You can download older versions of Unsung Anthem from [the releases page](https://github.com/anttikivi/unsung-anthem/releases).
* **Can you reliably reproduce the issue?** If not, provide details about how often the problem happens and under which conditions it normally happens.

Include details about your configuration and environment:

* **Which version of Obliging Ode and Unsung Anthem are you using?** You can get the exact version by running `anthem -v` in your terminal.
* **What’s the name and version of the OS you’re using**?
* **Are you running Obliging Ode and Unsung Anthem in a virtual machine?** If so, which VM software are you using and which operating systems and versions are used for the host and the guest?
* **Which keyboard layout are you using?** Are you using a US layout or some other layout?

### Suggesting Enhancements

This section guides you through submitting an enhancement suggestion for Obliging Ode or Unsung Anthem, including completely new features and minor improvements to existing functionality. Following these guidelines helps the maintainers and the community understand your suggestion :pencil: and find related suggestions :mag_right:.

Before creating enhancement suggestions, please check [this list](#before-submitting-an-enhancement-suggestion) as you might find out that you don’t need to create one. When you are creating an enhancement suggestion, please [include as many details as possible](#how-do-i-submit-a-good-enhancement-suggestion). Fill in [the template](.github/ISSUE_TEMPLATE/feature_request.md), including the steps that you imagine you would take if the feature you’re requesting existed.

#### Before Submitting an Enhancement Suggestion

* **Check the [debugging guide](#)** for tips — you might discover that the enhancement is already available. Most importantly, check if you’re using [the latest version of Obliging Ode and Unsung Anthem](#) and if you can get the desired behaviour by changing [the settings of Obliging Ode and Unsung Anthem](#).
* **Perform a [cursory search](https://github.com/issues?q=is%3Aissue+user%3Aanttikivi)** to see if the enhancement has already been suggested. If it has, add a comment to the existing issue instead of opening a new one.

#### How Do I Submit a (Good) Enhancement Suggestion?

Enhancement suggestions are tracked as [GitHub issues](https://guides.github.com/features/issues). Just create an issue on that repository and provide the following information:

* **Use a clear and descriptive title** for the issue to identify the suggestion.
* **Provide a step-by-step description of the suggested enhancement** in as many details as possible.
* **Provide specific examples to demonstrate the steps**. Include copiable snippets which you use in those examples, as [Markdown code blocks](https://help.github.com/articles/markdown-basics#multiple-lines).
* **Describe the current behaviour** and **explain which behaviour you expected to see instead** and why.
* **Include screenshots and animated GIFs** which help you demonstrate the steps or point out the part of Obliging Ode or Unsung Anthem which the suggestion is related to. You can use [this tool](http://www.cockos.com/licecap) to record GIFs on macOS and Windows, and [this tool](https://github.com/colinkeenan/silentcast) or [this tool](https://github.com/GNOME/byzanz) on Linux.
* **Specify which version of Obliging Ode and Unsung Anthem you’re using.** You can get the exact version by running `anthem -v` in your terminal.
* **Specify the name and version of the OS you’re using.**

### Your First Code Contribution

Unsure where to begin contributing to Obliging Ode and Unsung Anthem? You can start by looking through these `good first issue` and `help wanted` issues:

* [`good first issue`][good-first-issue]: issues which should only require a few lines of code and a test or two.
* [`help wanted`][help-wanted]: issues which should be a bit more involved than `good first issue` issues.

Both issue lists are sorted by total number of comments. While not perfect, number of comments is a reasonable proxy for impact a given change will have.

### Pull Requests

Please follow these steps to have your contribution considered by the maintainers:

1. Follow the instructions in the [pull request template](PULL_REQUEST_TEMPLATE.md).
2. Follow the [style guides](#style-guides).
3. After you submit your pull request, verify that all [status checks](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/about-status-checks) are passing.

    <details><summary>What if the status checks are failing?</summary>If a status check is failing and you believe that the failure is unrelated to your change, please leave a comment on the pull request explaining why you believe the failure is unrelated. A maintainer will re-run the status check for you. If we conclude that the failure was a false positive, then we will open an issue to track that problem with our status check suite.</details>

While the prerequisites above must be satisfied prior to having your pull request reviewed, the reviewers may ask you to complete additional design work, tests, or other changes before your pull request can be ultimately accepted.

## Style Guides

### Git Commit Messages

* Use the present tense (‘Add feature’, not ‘Added feature’)
* Use the imperative mood (‘Move cursor to...’ not ‘Moves cursor to...’)
* Try to limit the first line to 72 characters or fewer
* Reference issues and pull requests liberally after the first line

### C++ Style Guide

<!-- TODO -->

### Python Style Guide

<!-- TODO -->

### Documentation Style Guide

<!-- TODO -->

[good-first-issue]:https://github.com/search?q=is%3Aopen+is%3Aissue+label%3Agood+first+issue+user%3Aanttikivi+sort%3Acomments-desc
[help-wanted]:https://github.com/search?q=is%3Aopen+is%3Aissue+label%3Ahelp+wanted+user%3Aanttikivi+sort%3Acomments-desc
