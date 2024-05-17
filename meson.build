project('tickets app','cpp',
    version: '0.0.1',
    default_options: [
                'warning_level=3', 
                'cpp_std=c++23',
                'c_std=c23',
                'default_library=static',
                'buildtype=debug',
                'cpp_module=true'
                ]
)

build_options = [
    '-O2',  # Настройка оптимизации
    '-Wall',  # Включение всех предупреждений
]

if host_machine.system() == 'windows'
    build_options += [
        '/EHsc',  # Включение обработки исключений
        '/MD',  # Статическая линковка с MSVCRT
    ]
endif

add_project_arguments(build_options, language : 'cpp')

cdata = configuration_data()
cdata.set('MOCK_TICKET_PATH', '"mock_tickets.bin"')
cdata.set('SHOW_LIMIT', 5)


config_h = configure_file(
    output: 'appconf.h',
    configuration: cdata,

)
appconf_includes = include_directories('.')

subdir('module')
subdir('navigation')
subdir('cmd')
