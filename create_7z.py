import py7zr


def dist(meson):
    # Собираем архив tar.xz как обычно
    meson.add_dist_script('python', 'create_7z.py')


def create_7z(project, version):
    with py7zr.SevenZipFile(f'{project}-{version}.7z', mode='w') as archive:
        archive.writeall(f'{project}-{version}', arcname=f'{project}-{version}')
