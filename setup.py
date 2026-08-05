from setuptools import find_packages, setup

package_name = 'autonomy_led_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='ShawnJones',
    maintainer_email='sdj0016@mix.wvu.edu',
    description='TODO: Package description',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'autonomy_led_subscriber = autonomy_led_pkg.autonomy_led_subscriber:main'
        ],
    },
)
