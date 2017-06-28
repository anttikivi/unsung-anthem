# anthem_build_support/github.py ---------------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

import os

import diagnostics

from variables import ANTHEM_SOURCE_ROOT

import requests

GITHUB_API_URL = 'https://api.github.com'
GITHUB_DEFAULT_HEADERS = {'User-Agent': 'venturesomestone',
                          'Accept': 'application/vnd.github.v3+json'}


def print_rest(message):
    print('[GitHub REST API v3] ' + message)


def get_json(url, key, value, headers=None):
    """
    Retrieves the JSON node of the given key from the wanted list of
    JSON values of GitHub REST API v3.

    :param url: The sub-URL.
    :param key: The key of the value that is used to check whether or not the
                JSON node is the correct one.
    :param value: The value that the value of the wanted key should match.
    :param headers: Additional headers for the GET call.
    :return: The JSON node.
    """

    if headers is None:
        headers = {}

    # Set the URL to the one for getting the wanted value.
    call_url = GITHUB_API_URL + url

    # Set the headers for the call.
    call_headers = GITHUB_DEFAULT_HEADERS

    # If there are additional headers, add them to the final headers used in
    # the call.
    if len(headers) > 0:
        for additional_header in headers.keys():
            call_headers[additional_header] = headers[additional_header]

    print_rest('Calling GET on URL ' + call_url)
    print_rest('Using headers:')

    # Print the information for the headers.
    for header in call_headers.keys():
        print(header + ': ' + call_headers[header])

    # Make the call.
    request = requests.get(url=call_url, headers=call_headers)

    print_rest('The status code of the call is ' + str(request.status_code))

    # Save the results as JSON as they should be in that format.
    request_data = request.json()

    print_rest('Searching for JSON node with '
               + value
               + ' as its value of '
               + key
               + ' from data got URL '
               + url
               + '.')

    # Iterate over the entries.
    for json in request_data:

        # Check if the value of the key matches the wanted value.
        if not (json[key] == value):
            print_rest('JSON node from '
                       + url
                       + ' with '
                       + json[key]
                       + ' as the value of '
                       + key
                       + ' does not match '
                       + value
                       + '. Moving on to the next node.')
            continue
        else:
            print_rest('JSON node from '
                       + url
                       + ' with '
                       + json[key]
                       + ' as the value of '
                       + key
                       + ' does match '
                       + value
                       + '. Returning.')
            return json

    return None


def get(url, key, check_key, value, headers=None):
    """
    Retrieves the JSON entry value of the given key from the wanted list of
    JSON values of GitHub REST API v3.

    :param url: The sub-URL.
    :param key: The key of the wanted value.
    :param check_key: The key of the value that is used to check whether or
                      not the JSON node is the correct one.
    :param value: The value that the value of the wanted key should match.
    :param headers: Additional headers for the GET call.
    :return: The value.
    """

    if headers is None:
        headers = None

    print_rest('Getting the value of '
               + key
               + ' from JSON with '
               + value
               + ' as its value of '
               + check_key
               + ' in '
               + url
               + '.')

    # Get the wanted JSON node.
    json_node = get_json(url=url, key=check_key, value=value, headers=headers)

    # Check if the JSON is got correctly.
    if json_node is None:
        diagnostics.fatal('Unable to find the wanted JSON node.')

    print_rest('The value of '
               + key
               + ' found from JSON node with '
               + value
               + ' as its value of '
               + check_key
               + ' in '
               + url
               + ' is '
               + str(json_node[key])
               + '.')

    # Return the value.
    return json_node[key]


def download_asset(owner, repository, release_name, asset_name, destination):
    """
    Downloads a single file from the GitHub releases.

    :param owner: The owner of the repository.
    :param repository: The name of the repository.
    :param release_name: The name of the release.
    :param asset_name: The name of the asset to look for.
    :param destination: The destination file name of the asset relative to
                        ANTHEM_SOURCE_ROOT.
    :return:
    """

    # Start by getting the release id as it is needed in order to get the
    # release data.
    release_id = get(url='/repos/' + owner + '/' + repository + '/releases',
                     key='id',
                     check_key='name',
                     value=release_name)

    # Get the asset URL of the wanted asset from the release.
    asset_url = get(url='/repos/'
                        + owner
                        + '/'
                        + repository
                        + '/releases/'
                        + str(release_id)
                        + '/assets',
                    key='url',
                    check_key='name',
                    value=asset_name)

    asset_call_headers = {'Accept': 'application/octet-stream'}

    # Get the asset with the URL.
    asset_request = requests.get(asset_url,
                                 headers=asset_call_headers,
                                 stream=True)

    # Check whether or not the request is redirected.
    if asset_request.status_code == 302:
        # TODO
        print('redirected')
    elif asset_request.status_code == 200:

        # Set the full path to the destination file.
        local_filename = os.path.join(ANTHEM_SOURCE_ROOT, destination)

        print_rest('The asset is not redirected. Now streaming it to '
                   + str(local_filename))

        # Stream the file to the final destination.
        with open(local_filename, 'wb') as f:
            for chunk in asset_request.iter_content(chunk_size=1024):
                if chunk:
                    f.write(chunk)

        print_rest('Finished streaming from '
                   + asset_url
                   + ' to '
                   + str(local_filename))

    else:
        diagnostics.fatal('Cannot download the file as the HTTP request '
                          'returned invalid code ('
                          + str(asset_request.status_code)
                          + ')')


def download_source(owner, repository, release_name, destination):
    """
    Downloads a single source archive from the GitHub releases.

    :param owner: The owner of the repository.
    :param repository: The name of the repository.
    :param release_name: The name of the release.
    :param destination: TODO
    :return: The short SHA of the release tag commit.
    """

    # Start by getting the URL of the tarball of the release source.
    tarball_url = get(url='/repos/' + owner + '/' + repository + '/releases',
                      key='tarball_url',
                      check_key='name',
                      value=release_name)

    tarball_request = requests.get(url=tarball_url,
                                   headers=GITHUB_DEFAULT_HEADERS)

    # Set the full path to the destination file.
    local_filename = os.path.join(ANTHEM_SOURCE_ROOT, destination)

    # Stream the file to the final destination.
    with open(local_filename, 'wb') as f:
        for chunk in tarball_request.iter_content(chunk_size=1024):
            if chunk:
                f.write(chunk)

    print_rest('Finished streaming from '
               + tarball_url
               + ' to '
               + str(local_filename))


def get_release_sha(owner, repository, release_name):
    """
    Gets the SHA of the given release.

    :param owner: The owner of the repository.
    :param repository: The name of the repository.
    :param release_name: The name of the release.
    :return: The SHA of the release tag commit.
    """

    # Start by getting the name of the tag of the release for getting the
    # SHA of the tag.
    tag_name = get(url='/repos/' + owner + '/' + repository + '/releases',
                   key='tag_name',
                   check_key='name',
                   value=release_name)

    # Get the tag JSON for getting the tag SHA.
    tag = get_json(url='/repos/' + owner + '/' + repository + '/tags',
                   key='name',
                   value=tag_name)

    # Return the SHA of the tag commit.
    return tag['commit']['sha']


def get_release_short_sha(owner, repository, release_name):
    """
    Gets the SHA of the given release.

    :param owner: The owner of the repository.
    :param repository: The name of the repository.
    :param release_name: The name of the release.
    :return: The short 7-character SHA of the release tag commit.
    """

    # Start by getting the SHA of the tag.
    sha = get_release_sha(owner, repository, release_name)

    short_sha_list = []

    # Not-very-Pythonic hack.
    loop_count = 0

    for c in str(sha):
        short_sha_list += [c]
        loop_count += 1
        if 7 == loop_count:
            break

    # Create a string for the short SHA.
    short_sha = ''.join(short_sha_list)

    return short_sha
