import requests
import time
import os
import csv


MAX_ROOSTER_COUNT = 74
BASE_URL = 'https://test-khapi.frannsoft.com/api'


# -----Class-----
#I created this object
class CharacterData:
    def __init__(self, name, owner_id, thumbnail_url,
                 display_name, moves_url):
        self.name = name
        self.owner_id = str(owner_id)
        self.thumbnail_url = thumbnail_url
        self.display_name = display_name
        self.moves_url = moves_url

    def print_data(self):
        return self.name + ' ' + self.owner_id + ' ' + \
               self.thumbnail_url + ' ' + self.display_name + ' ' + \
               self.moves_url
# ----------------


# ----Functions----
def create_folder(directory):
    try:
        if not os.path.exists(directory):
            os.makedirs(directory)
    except OSError:
        print('Could not create folder')


#I created this function
def check_response_code(response_code, url):
    if response_code == 200 or 404:
        return response_code
    else:
        print('Error: ' + str(response_code) + '\n' + url)
        input('Press enter to exit')
        exit()


'''The 404 error is checked here because some characters don't have
their frame data yet and when called, it sends a 404 as the response
code. When calling the create_frame_data file it ignores the 404 error.'''
#I created this function
def error_404(url):
    print("404 error\nUrl: " + url + "\n")
    input("Press enter to exit")
    exit()


def get_character_values(character_data_json):
    character_values = []

    for key in ['Name', 'OwnerId', 'DisplayName']:
        character_values.append(character_data_json[key])

    character_values.insert(2, create_thumbnail_url(character_values[2]))
    character_values.append(character_data_json['Related']['Ultimate']['Moves'])

    return character_values


#I created this function
def create_thumbnail_url(display_name):
    thumbnail_url = 'http://kuroganehammer.com/images/ultimate/character/'

    if display_name == 'Game & Watch':
        return thumbnail_url + 'mr_game_and_watch.png'
    elif display_name == 'Rosalina & Luma':
        return thumbnail_url + 'rosalina.png'
    elif display_name == 'PAC-MAN':
        return thumbnail_url + 'pac_man.png'
    elif display_name == 'Piranha Plant':
        return thumbnail_url + 'pot_plant.png'

    display_name = display_name.replace('.', '').replace(' ', '_')

    return thumbnail_url + display_name + '.png'


def create_thumbnail_picture(thumbnail_url, display_name):
    thumbnail = requests.get(thumbnail_url)

    response_code = check_response_code(thumbnail.status_code,
                                        thumbnail_url)
    if response_code == 404:
        return

    file_path = 'Character Data/' + display_name
    with open(file_path + '/' + display_name + '.png', 'wb') as handler:
        handler.write(thumbnail.content)


def create_frame_data_file(move_set_url, name):
    move_set_data = requests.get(move_set_url)

    file_path = 'Character Data/' + name

    response_code = check_response_code(move_set_data.status_code, move_set_url)
    if response_code != 404:
        with open(file_path + '/' + name + '_frame_data.csv',
                  'w', newline='') as infile:
            writer = csv.writer(infile)
            writer.writerow(['Move Type', 'Name', 'Hitbox Active',
                             'First Actionable Frame', 'Landing Lag',
                             'Auto Cancel', ''])
            writer.writerows(get_moves_list(move_set_data.json()))
    else:
        with open(file_path + '/' + name + '_frame_data.csv', 'w') as infile:
            infile.write('None')


def get_moves_list(move_set_json_data):
    moves_list = []

    for i in range(0, len(move_set_json_data)):
        moves_data_list = []

        for key in ['MoveType', 'Name', 'HitboxActive',
                    'FirstActionableFrame', 'LandingLag',
                    'AutoCancel']:
            if(move_set_json_data[i][key] is None):
                moves_data_list.append('None')
            else:
                value = move_set_json_data[i][key]
                value = value.replace(',', '/')
                value = value.replace('"', '')
                value = value.replace(' ', '')
                moves_data_list.append(value)
        moves_data_list.append('')

        moves_list.append(moves_data_list)

    return moves_list


def create_character_data_file(character_value_list):
    file_path = 'Character Data'
    with open(file_path + '/' + 'character_values.csv',
              'w', newline='') as infile:
        writer = csv.writer(infile)
        writer.writerow(['Owner Id', 'Name', 'Display Name'])
        writer.writerows(character_value_list)
# -----------------


def main():
    character_data_url = BASE_URL + '/characters/'
    character_object_list = []

    start = time.time()
    create_folder('Character Data')
    #Puts the data in an object
    for i in range(1, MAX_ROOSTER_COUNT + 1):
        character_url_request = requests.get(character_data_url + str(i))

        response_code = check_response_code(character_url_request.status_code,
                                            character_data_url + str(i))
        if response_code == 404:
            error_404(character_data_url + str(i))

        data_list = get_character_values(character_url_request.json())
        character_object_list.append(CharacterData(data_list[0], data_list[1],
                                                   data_list[2], data_list[3],
                                                   data_list[4]))
    end = time.time()
    print("Time to get character data and put it in an object: " +
          str(end - start) + " sec(s)")

    start = time.time()
    character_values = []
    #Makes the files with the data
    for i in range(0, MAX_ROOSTER_COUNT):
        name = character_object_list[i].name

        create_folder('Character Data/' + name)

        character_values.append([character_object_list[i].owner_id,
                                 character_object_list[i].name,
                                 name, ''])

        create_thumbnail_picture(character_object_list[i].thumbnail_url, name)

        create_frame_data_file(character_object_list[i].moves_url, name)

    create_character_data_file(character_values)
    end = time.time()
    print("Time to create the Character Data folder and files: " +
          str(end - start) + " sec(s)")


if __name__ == "__main__":
    main()
